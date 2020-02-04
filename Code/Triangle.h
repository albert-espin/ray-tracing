#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include "Plane.h"


// Classe que representa un triangle, que és la delimitació d'un pla
// fent servir tres vèrtexs connectats dos a dos
class Triangle : public Plane
{

public:

    Triangle(vec3 a, vec3 b, vec3 c, Material * m);

    ~Triangle() {}

    bool hit(const Ray &r, float t_min, float t_max, HitInfo &rec) const;

private:

    // vèrtexs del triangle a l'espai
    std::vector<vec3> vertices;

    // normal del pla del triangle
    vec3 normal;

};

#endif // TRIANGLE_H
