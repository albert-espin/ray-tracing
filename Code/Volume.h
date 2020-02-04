#ifndef VOLUME_H
#define VOLUME_H

#include "Object.h"
#include "Cube.h"
#include "Isotropic.h"

// Objecte volum, representa un cos volumètric, no format per superfícies sinó
// que defineix un cert comportament en la regió a l'espai que ocupa
class Volume : public Object
{
public:
    Volume(int dimX, int dimY, int dimZ, int density, Isotropic * mat);
    virtual ~Volume();

    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const;


private:

    // dimensions del volum
    int dimX, dimY, dimZ;

    // densitat del volum
    int density;

    // centre del volum
    // NOTA: a l'enunciat es força que sigui (0,0,0) i no s'indica com a paràmetre
    // al constructor al joc de proves del pdf, per tant entenem que no es vol, però
    // tindria sentit fer-ho (no ho fem per respectar signatures)
    vec3 center = vec3(0,0,0);

    // cub virtual en què es troba el volum
    Cube * cube;

};

#endif // VOLUME_H
