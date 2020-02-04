#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

// classe que representa una llum puntual
class PointLight : public Light
{
public:

    PointLight(vec3 position, vec3 ambient, vec3 diffuse, vec3 specular, float attenuation_a, float attenuation_b, float attenuation_c);
};

#endif // POINTLIGHT_H
