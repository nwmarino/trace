//
//  Material.h
//

#pragma once

#include "Hittable.h"

class Material {
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
        return false;
    }
};

class Lambertian : public Material {
    Color albedo = {};

public:
    Lambertian(const Color& albedo) : albedo(albedo) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
        auto dir = rec.normal + randomUnit();

        if (dir.near_zero())
            dir = rec.normal;
        
        scattered = Ray(rec.p, dir);
        attenuation = albedo;
        return true;
    }
};

class Metal : public Material {
    Color albedo = {};
    double fuzz = 0.0;
    
public:
    Metal(const Color& albedo, double fuzz) 
        : albedo(albedo)
        , fuzz(fuzz) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
        vec3 reflected = reflect(r_in.dir, rec.normal);
        reflected = unit(reflected) + (fuzz * randomUnit());
        scattered = Ray(rec.p, reflected);
        attenuation = albedo;
        return (dot(scattered.dir, rec.normal) > 0);
    }
};
