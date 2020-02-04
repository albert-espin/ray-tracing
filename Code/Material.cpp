#include "Material.h"



Material::Material():
    diffuse(1.0f)
{}

Material::Material(vec3 diffuse) {
    this->diffuse = diffuse;
    this->alpha = 1.f;
    this->shininess = 1.f;

}

Material::Material(vec3 diffuse, vec3 ambient, vec3 specular, float alpha=1.f, float shininess=1.f) {
    this->diffuse = diffuse;
    this->ambient = ambient;
    this->alpha = alpha;
    this->specular = specular;
    this->shininess = shininess;
}

Material::~Material()
{}

vec3 Material::getDiffuse() const
{
    return diffuse;
}

vec3 Material::getAmbient() const
{
    return ambient;
}

float Material::getAlpha() const
{
    return alpha;
}

vec3 Material::getSpecular() const
{
    return specular;
}

float Material::getShininess() const
{
    return shininess;
}


vec3 Material::RandomInSphere() const {
    vec3 p;
    do {
        p = 2.0f*vec3(drand48(),drand48(),drand48()) - vec3(1,1,1);
    } while (glm::length(p) >=  1.0f);
    return p;
}

