#include "PointLight.h"

PointLight::PointLight(vec3 position, vec3 ambient, vec3 diffuse, vec3 specular, float attenuation_a, float attenuation_b, float attenuation_c)
    : Light(position, ambient, diffuse, specular, attenuation_a, attenuation_b, attenuation_c)
{}
