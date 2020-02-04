#include "Plane.h"
#include <iostream>


Plane::Plane(vec3 norm, vec3 p, Material *m) : Object(m)
{
    normal = norm;
    point = p;
}

vec3 Plane::getNormal() const
{
    return normal;
}


bool Plane::hit(const Ray& r, float t_min, float t_max, HitInfo& rec) const {

    // enllaç de la fórmula utilitzada:
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection

   vec3 rayOrigin(r.initialPoint());
   vec3 rayDir(r.dirVector());

    // calculem el producte escalar entre la normal del pla i el vector director del pla normalitzat
    float dotProduct = dot(normal, rayDir);

    // si el producte escalar és zero (amb un petit marge d'error de coma flotant), sabem que el raig
    // mai podrà interseccionar amb el pla, per tant només seguim fent comprovacions en cas contrari
    if (abs(dotProduct) > 0.00001){

        // càlcul del paràmetre t, que representa la profunditat en què el raig intersecciona amb
        // el pla
        vec3 planePointMinusRayOrigin = point - rayOrigin;
        float t = dot(planePointMinusRayOrigin, normal) / dotProduct;

        // si el valor t d'intersecció pertany al rang estudiable, considerem que hi ha intersecció
        // efectiva i donem valors al hitInfo
        if (t >= t_min && t <= t_max){

            rec.t = t;
            rec.p = r.pointAtParameter(rec.t);

            // la normal d'intersecció coincideix amb la del pla si s'intersecciona amb la cara
            // anterior del pla (producte escalar negatiu), i s'obté multiplicant per -1 en cas
            // contrari
            rec.normal = normal * (dotProduct > 0 ? -1.f : 1.f);

            rec.mat_ptr = material;

            return true;
        }
    }


    return false;
}
