#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
class material;

// each ray has a hit record that stores info of the hit like the normal, the material, the point, if its 
//the front face of an object, and t the interpolator of the ray
class hit_record 
{
  public:
    point3 p;
    vec3 normal;
    // when ray hits a object surface, it points to the objects material pointer. This can be used in 
    //raycolor when it gest hitrecord to call functions from the material pointter
    shared_ptr<material> mat;
    double t;
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        // Sets the hit record normal vector.
        // checks if the ray hits the front face of object and assigns normal in opposite 
        // direction of ray

        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable 
{
  public:
    virtual ~hittable() = default;

    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif