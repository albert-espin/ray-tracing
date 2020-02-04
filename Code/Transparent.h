#ifndef TRANSPARENT_H
#define TRANSPARENT_H

#include "Material.h"

class Transparent : public Material
{
public:

    Transparent(const vec3 transparent, float refractionIndex);
    Transparent(vec3, float, vec3, vec3, vec3, float, float);
    virtual ~Transparent();
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const;

    // component transparent
    vec3 transparent;

    // índex de refracció
    float refractionIndex;

};

#endif // TRANSPARENT_H
