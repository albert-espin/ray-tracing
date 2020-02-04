#include "Light.h"

Light::Light(vec3& position, vec3& ambient, vec3& diffuse, vec3& specular, float a, float b, float c)
{
    this->position = position;

    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;

    this->attenuation_a = a;
    this->attenuation_b = b;
    this->attenuation_c = c;
}

vec3 Light::getPosition() const
{
    return position;
}

vec3 Light::getAmbient() const
{
    return ambient;
}

vec3 Light::getDiffuse() const
{
    return diffuse;
}

vec3 Light::getSpecular() const
{
    return specular;
}

float Light::obtainAttenuationFactorAtDistance(float dist)
{
    // el factor es calcula com 1 / (a + b*d + c*d*d)
    return 1.f / (attenuation_a + attenuation_b * dist + attenuation_c * dist * dist);
}
