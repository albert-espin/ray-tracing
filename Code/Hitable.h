#ifndef HITABLE_H
#define HITABLE_H


#include "Ray.h"

class Material;

class HitInfo
{
public:
    float     t; // t del raig on s'ha intersecat
    vec3      p;  // punt del raig on hi ha la intersecció
    vec3      normal; // normal en el punt d'intersecció
    const Material *mat_ptr; // material de l'objecte que s'ha intersectat

    HitInfo():
        t(std::numeric_limits<float>::infinity()),
        p(0.0f),
        normal(0.0f),
        mat_ptr(NULL)
        {}

    //  "operator =" per la classe  IntersectInfo
    HitInfo &operator =(const HitInfo &rhs) {
      p = rhs.p;
      mat_ptr = rhs.mat_ptr;
      normal = rhs.normal;
      t = rhs.t;
      return *this;
    }
};

class Hitable
{
public:
    Hitable();
    ~Hitable();
    // S'obliga a implementar-lo en les classes filles: es un metode abstracte
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const = 0;
};

#endif // HITABLE_H
