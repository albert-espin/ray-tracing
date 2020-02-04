#ifndef CUBE_H
#define CUBE_H
#include "Object.h"

// Classe que representa un cub alineat amb els eixos
class Cube : public Object
{
public:

    Cube(vec3 b0, vec3 b1, Material * m);

    ~Cube() {}

    bool hit(const Ray &r, float t_min, float t_max, HitInfo &rec) const;

    // hit que retorna les T del punt mínim i màxim de la intersecció, no solament el mínim
    bool hitMinMax(const Ray & r, float t_min, float t_max, float & tmin, float & tmax) const;

private:

    // punts delimitadors del cub
    vec3 minBound;
    vec3 maxBound;


    // calcula i retorna la normal d'un raig que interseca amb el cub
    // en el punt passat per paràmetre
    vec3 obtainNormalAtIntersectionPoint(vec3 intersectionPoint) const;

};

#endif // CUBE_H
