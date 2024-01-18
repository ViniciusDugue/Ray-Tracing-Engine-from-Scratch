#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
  public:
    // spheres can have a shared pointer to specific material instances
    sphere(point3 _center, double _radius, shared_ptr<material> _material)
      : center(_center), radius(_radius), mat(_material) {}

    
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override 
    {
      // takes in a ray and returns true or false if ray hits sphere
      // updates hit record rec with surface normal, opposite of ray direction 

      // this is done by calculating the roots t, where a ray of points P(t) intersects the equation for the surface of  
      // the sphere:(x-Cx)^2 + (y-Cy)^2 + (z-Cz)^2 = r^2 where C is the sphere center

      vec3 oc = r.origin() - center;
      auto a = r.direction().length_squared();
      auto half_b = dot(oc, r.direction());
      auto c = oc.length_squared() - radius*radius;

      auto discriminant = half_b*half_b - a*c;
      if (discriminant < 0) return false;
      auto sqrtd = sqrt(discriminant);

      // Find the nearest root that lies in the acceptable range.
      auto root = (-half_b - sqrtd) / a;
      if (!ray_t.surrounds(root)) 
      {
        root = (-half_b + sqrtd) / a;
        if (!ray_t.surrounds(root))
          return false;
      }

      rec.t = root;
      rec.p = r.at(rec.t);
      vec3 outward_normal = (rec.p - center) / radius;
      rec.set_face_normal(r, outward_normal);
      rec.mat = mat;

      return true;
    }

  private:
    point3 center;
    double radius;
    shared_ptr<material> mat;
};

// x2+y2+z2=r2
// if (x,y,z) is inside the sphere, then x2+y2+z2<r2
// if (x,y,z) is outside the sphere, then x2+y2+z2>r2
#endif