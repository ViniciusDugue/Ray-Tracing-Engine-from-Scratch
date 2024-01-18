#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

// bringing the code into the scope to avoid hasving to use std::
using std::shared_ptr;
using std::make_shared;

// stores list of hittable records
class hittable_list : public hittable 
{
    public:
        std::vector<shared_ptr<hittable>> objects;

        hittable_list() {}
        hittable_list(shared_ptr<hittable> object) { add(object); }
        
        void clear() { objects.clear(); } // empties hittable list
        
        void add(shared_ptr<hittable> object) //adds hittable to list
        {
            objects.push_back(object);
        }

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override 
        {
            hit_record temp_rec;
            bool hit_anything = false;
            auto closest_so_far = ray_t.max;

            // loops through objects in hittables list to find the nearest ray hit and stores the nearest hit in the ray hitrecord
            for (const auto& object : objects) {
                if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) 
                {
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }

            return hit_anything;
        }
};

#endif