#include "Metal.h"


Metal::Metal(const vec3& color): Material(specular) {}


Metal::Metal(vec3 diffuse, vec3 ambient, vec3 specular, float alpha, float shininess)

    : Material(diffuse, ambient, specular, alpha, shininess)
{}


Metal::~Metal()
{}


bool Metal::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const  {

    // el punt d'origen del raig de reflexió
    scattered.origin = rec.p;

    // direcció del raig reflectit
    vec3 r = reflect(normalize(r_in.dirVector()), normalize(rec.normal));

    // valor entre 0 i 1 per donar aleatorietat al raig
    float fuzzy = 0.01f;
    scattered.direction = r + fuzzy * RandomInSphere();

    // en un material metàl·lic, el valor de color és l'especular
    color = specular;

    return true;
}



