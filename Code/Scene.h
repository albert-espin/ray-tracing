#ifndef SCENE_H
#define SCENE_H

#include <limits> //per obtenir els valors infinit dels tipus
#include <vector>
#include "Ray.h"
#include "Hitable.h"

// objectes
#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Cube.h"
#include "BoundaryObject.h"
#include "Volume.h"

// materials
#include "Lambertian.h"
#include "Metal.h"
#include "Transparent.h"
#include "Isotropic.h"

// textures
#include "TextureConstant.h"
#include "TextureChecker.h"

//camera
#include "Camera.h"

// llums
#include "Light.h"
#include "PointLight.h"


class Scene: public Hitable
{
public:
    Scene();
    virtual ~Scene();

    // Funcio que calcula la interseccio del raig r amb l'escena. Guarda la informacio
    // del punt d'interseccio més proper a t_min, punt que està entre t_min i t_max.
    // Retorna cert si existeix la interseccio, fals, en cas contrari
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const;

    // Funcio recursiva que calcula el color. Inicialment es
    // es crida a cada pixel. Tambe es crida en calcular les ombres o les reflexions.
    vec3 ComputeColor (Ray &ray, int depth );

    // calcula un valor de color amb shade mitjançant Blinn-Phong tenint en compte
    // el hitInfo i el raig passats per paràmetre
    vec3 blinnPhong(vec3 point, vec3 normal, const Material *material, bool ombra);

    // configura la llum d'ambient global de l'escena
    void setAmbientLight(vec3 &ambient);

    // Vector d'objectes continguts a l'escena
    std::vector<Object*> objects;

    // Vector de llums de l'escena
    std::vector<Light *> lights;

    // Camera: on está l'observador
    Camera *cam;


private:

    // afegeix objectes a l'escena
    void RandomScene();

    // afegeix llums a l'escena
    void setUpLights();


    // es computa el factor d'ombra en un punt (entre 0 i 1) respecte una llum
    // fent servir el raig del punt a aquesta llum
    float computeShadowFactor(Ray & pointToLightRay, float light_T);




    // intensitat de la llum de l'ambient global de l'escena
    vec3 globalAmbientLightIntensity;

    // constants de valors mínim i màxim de t per tenir en compte al raytracing
    const float T_MIN = 0;
    const float T_MAX = 1000;

    // epsilon per evitar l'autointersection dels objectes amb el hit
    const float EPSILON = 0.001;

    const int MAXDEPTH = 10;

};

#endif // SCENE_H
