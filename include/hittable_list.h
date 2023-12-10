#pragma once

#include "hittable.h"

#include <vector>
#include <memory>

class HittableList : public Hittable {
    public:
        HittableList() {}
        HittableList(std::shared_ptr<Hittable> object) { add(object); }

        void clear() { objects_.clear(); }
        void add(std::shared_ptr<Hittable> object) { objects_.push_back(object); }

        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

    public:
        std::vector<std::shared_ptr<Hittable>> objects_;
};

bool HittableList::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    HitRecord temp_rec;
    bool hit_anything = false;

    auto closest_so_far = t_max;
    for (const auto& object : objects_) {
        if (object->hit(r, t_min, t_max, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;

}