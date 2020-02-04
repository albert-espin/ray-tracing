#ifndef MATERIAL_H
#define MATERIAL_H


#include "Ray.h"
#include "Hitable.h"

// Classe abstracte Material. Totes les seves filles hauran de definir el metode abstracte sccater
class Material
{
public:

    Material();

    Material(vec3 diffuse);

    Material(vec3 diffuse, vec3 ambient, vec3 specular, float alpha, float shininess);

    ~Material();

    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const = 0;


    // Retorna la component difusa
    vec3 getDiffuse() const;

    // Retorna la component ambient
    vec3 getAmbient() const;

    // Retorna l'opacitat
    float getAlpha() const;

    // Retorna la component especular
    vec3 getSpecular() const;

    // Retorna la shininess
    float getShininess() const;




    // component difusa
    vec3 diffuse;


protected:

    // component ambient
    vec3 ambient;

    // opacitat del material
    float alpha;

    // component especular
    vec3 specular;

    // exponent de reflexió especular
    float shininess;

    vec3 RandomInSphere() const;
};

#endif // MATERIAL_H
