#pragma once

#include <vector>
#include "Ray.h"
#include "Hitable.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Transparent.h"
#include "Isotropic.h"


// Es la classe pare de tots els objectes que s'han de visualitzar. Es fa una classe Objectes que hereda de Hitable
// i ha d'implementar el metode hit
class Object: public Hitable {
  public:
    Object(Material *mat);
    virtual ~Object();

    // Metode a implementar en les classes filles: es un metode abstracte
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const = 0;


  protected:
    Material *material;   // Material de l'objecte
};

