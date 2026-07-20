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

class Dialectric : public Material {
    double refraction_index = 0.0;

public:
    Dialectric(double refraction_index) : refraction_index(refraction_index) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
        attenuation = Color(1.0, 1.0, 1.0);
        double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;

        vec3 unit_dir = unit(r_in.dir);
        double cos_theta = std::fmin(dot(-unit_dir, rec.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = ri * sin_theta > 1.0;
        vec3 dir = {};

        if (cannot_refract || reflectance(cos_theta, ri) > randomDouble()) {
            dir = reflect(unit_dir, rec.normal);
        } else {
            dir = refract(unit_dir, rec.normal, ri);
        }

        scattered = Ray(rec.p, dir);
        return true;
    }

private:
    static double reflectance(double cosine, double refraction_index) {
        auto r0 = (1 - refraction_index) / (1 + refraction_index);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }
};
