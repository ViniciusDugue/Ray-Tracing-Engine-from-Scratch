#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"
#include "color.h"
#include "hittable.h"

class hit_record;

class material {
  public:
    virtual ~material() = default;

    // takes in a ray, the color of potential scattered light, the ray that is scattered 
    // returns if the incident ray scatters or not, and updates scattered ray and attenuation color
    virtual bool scatter(
      const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};
// theres 2 options for modelling light scatter and reflectance:
//1. each ray can attenuate/weaken based on a materials R reflectance
//2. each ray can have a chance to scatter/continue bouncing with probability (R) or get absorbed 
//into the material with probability (1-R)
//3. each ray can scatter with a fixed probability (p) and attenuation is (albedo or reflectance/p)

// material that mixes the 2 and always scatters every ray and has low absorption (diffuse material)
class lambertian : public material 
{
  public:
    lambertian(const color& a) : albedo(a) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
    const override {
        auto scatter_direction = rec.normal + random_unit_vector();
        // Catch degenerate scatter direction and avoids rec.normal - randomunitvector = 0
        if (scatter_direction.near_zero())
          scatter_direction = rec.normal;

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

  private:
    color albedo;
};

// material that reflects all rays over the normal vector axis
// a bit of fuzzy reflection is added to the reflected rays to give the metal surfaces some bluriness or softness. This 
// simulates imperfections in the metal materials
// attenuation definition- a ray that attenuates when hitting a material, weakens in intensity/changes color
class metal : public material {
  public:
    metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
    const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz*random_unit_vector());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

  private:
    color albedo;
    float fuzz;
};

// material that either scatters/reflects or refracts rays (glass, water but this material is specifically for glass)
class dielectric : public material {
  public:
    dielectric(double index_of_refraction) : ir(index_of_refraction) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
    const override {
        attenuation = color(1.0, 1.0, 1.0);
        double refraction_ratio = rec.front_face ? (1.0/ir) : ir;

        vec3 unit_direction = unit_vector(r_in.direction());
        double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0; // calculate if ray refracts with probability of refraction ratio
        vec3 direction;

        if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())// makes sure the glass reflectance angle varies
            direction = reflect(unit_direction, rec.normal);
        else
            direction = refract(unit_direction, rec.normal, refraction_ratio);

        scattered = ray(rec.p, direction);
        return true;
    }

  private:
    double ir; // Index of Refraction

    // glass reflection varies with angle so here we calculate reflectivity based on angle
    static double reflectance(double cosine, double ref_idx) 
    {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1-ref_idx) / (1+ref_idx);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine),5);
    }
};
#endif