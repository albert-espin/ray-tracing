#include "Transparent.h"

#include<iostream>

Transparent::Transparent(const vec3 transparent, float refractionIndex): Material(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0, 0) {

    this->transparent = transparent;
    this->refractionIndex = refractionIndex;
}


Transparent::Transparent(vec3 transparent, float refractionIndex, vec3 diffuse, vec3 ambient, vec3 specular, float alpha, float shininess)

    : Material(diffuse, ambient, specular, alpha, shininess)
{

    this->transparent = transparent;
    this->refractionIndex = refractionIndex;
}


Transparent::~Transparent()
{}


bool Transparent::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const  {

    // el punt d'origen del raig de reflexió
    scattered.origin = rec.p;

    // N és la normal normalitzada
    vec3 N = normalize(rec.normal);

    // I és la direcció del raig incident normalitzada
    vec3 I = normalize(r_in.dirVector());

    // es calcula el producte escalar
    float dotValue = dot(I, N);

    // factor de refracció entre els medis
    float nit = refractionIndex;

    // si el producte escalar és zero cal girar la normal
    if (dotValue > 0){
        N = -N;
        nit = 1.f / nit;
    }

    // es calcula el paràmetre k
    float k = 1.f - (nit * nit) * (1.f - dotValue * dotValue);

    // es comprova que l'arrel de k sigui positiva
    // quan l'arrel és negativa es diu que hi ha reflexió total i pr tant només es té en compte el
    // vector reflectit
    if (k > 0.f) {

        // es calcula la direcció del raig refrectit
        scattered.direction = normalize(refract(I, N, nit));

        // factor K de refracció
        color = transparent;
    }

    else {

        // es calcula la direcció del raig reflectic
        scattered.direction = normalize(reflect(I, N));

        // factor K de reflexió
        color = specular;
    }



    return true;
}
