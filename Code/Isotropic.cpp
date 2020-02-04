#include "Isotropic.h"



Isotropic::Isotropic(Texture * texture) : Material()
{
    this->texture = texture;
}

Isotropic::~Isotropic()
{

}

bool Isotropic::scatter(const Ray &r_in, const HitInfo &rec, vec3 &color, Ray &scattered) const
{
    // es genera un raig secundari en una direcció arbitrària, com al cas del material lambertià
    vec3 target = rec.p + rec.normal + this->RandomInSphere();
    scattered = Ray(rec.p, target-rec.p);
    color = diffuse;
    return true;
}

vec3 Isotropic::getValue(vec3 p)
{
    return texture->value(p);
}
