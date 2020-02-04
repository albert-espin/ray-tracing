#include "Object.h"



Object::Object(Material *const mat)
  {
    material = mat;
  }

Object::~Object()
{
    if (dynamic_cast<Lambertian *>(material))
        delete (Lambertian *)material;

    else if (dynamic_cast<Metal *>(material))
        delete (Metal *)material;

    else if (dynamic_cast<Transparent *>(material))
        delete (Transparent *)material;

    else if (dynamic_cast<Isotropic *>(material))
        delete (Isotropic *)material;
}
