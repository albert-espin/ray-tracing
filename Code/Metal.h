#ifndef METAL_H
#define METAL_H

#include "Material.h"

class Metal : public Material {
public:
    Metal(const vec3& color);
    Metal(vec3, vec3, vec3, float, float);
    virtual ~Metal();
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const;

};

#endif // METAL_H
