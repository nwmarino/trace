//
//  Hittable.h
//

#pragma once

#include "Interval.h"
#include "Ray.h"
#include "Vec.h"

#include <memory>
#include <vector>

class Material;

struct HitRecord {
    point3 p = {};
    vec3 normal = {};
    std::shared_ptr<Material> mat = nullptr;
    double t = 0.0;
    bool front_face = false;

    void setFaceNormal(const Ray& r, const vec3& outward_normal) {
        front_face = dot(r.dir, outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable {
public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const = 0;
};

class HittableList : public Hittable {
public:
    std::vector<std::shared_ptr<Hittable>> objects = {};

    HittableList() = default;

    HittableList(std::shared_ptr<Hittable> object) {
        add(object);
    }

    void clear() {
        objects.clear();
    }

    void add(std::shared_ptr<Hittable> object) {
        objects.push_back(object);
    }

    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override {
        HitRecord temp = {};
        bool result = false;
        auto closest = ray_t.max;

        for (const auto& object : objects) {
            if (object->hit(r, Interval(ray_t.min, closest), temp)) {
                result = true;
                closest = temp.t;
                rec = temp;
            }
        }

        return result;
    }
};
