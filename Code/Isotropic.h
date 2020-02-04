#ifndef ISOTROPIC_H
#define ISOTROPIC_H

#include "Material.h"
#include "Texture.h"

// Material isotròpic, definit per una textura
class Isotropic : public Material
{
public:
    Isotropic(Texture * texture);
    virtual ~Isotropic();
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const;

    // retorna el valor en un opunt
    vec3 getValue(vec3 p);


private:

    // textura del material
    Texture * texture;

};

#endif // ISOTROPIC_H
