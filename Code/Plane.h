#ifndef PLANE_H
#define PLANE_H

#include "Object.h"

// Classe que representa un pla a l'espai
class Plane : public Object
{
public:

    Plane(vec3 norm, vec3 p, Material *m);

    ~Plane(){}

    // retorna la normal
    vec3 getNormal() const;

    bool hit(const Ray &r, float t_min, float t_max, HitInfo &rec) const;



private:

    // Normal del pla
    vec3 normal;

    // Punt de pas o referència del pla
    vec3 point;
};

#endif // PLANE_H
