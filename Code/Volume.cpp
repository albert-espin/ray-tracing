#include "Volume.h"



Volume::Volume(int dimX, int dimY, int dimZ, int density, Isotropic * mat) : Object(mat)
{
    this->dimX = dimX;
    this->dimY = dimY;
    this->dimZ = dimZ;
    this->density = density;

    // creació del cub
    vec3 centerToVertOffset = vec3(dimX/2., dimY/2., dimZ/2.);
    this->cube = new Cube(center + centerToVertOffset, center - centerToVertOffset, /*TEMP MATnullptr*/new Lambertian(vec3(1,0,0)));
}

Volume::~Volume()
{

}

bool Volume::hit(const Ray &r, float t_min, float t_max, HitInfo &info) const
{
    float tmin;
    float tmax;

    // per intersecar amb el volum, és imprescidible intersecar amb el
    // cub virtual on s'ubica
    if( cube->hitMinMax(r, t_min, t_max, tmin, tmax)){

        float deltaT = 0.1;
        int numIntervals = (tmax - tmin) / 0.1;

        float iterT;
        vec3 iterPoint;
        vec3 pointColor;

        // color i opacitats sortints, a calcular iterativament
        vec3 outColor = vec3(0,0,0);
        float outOpacity = 0.f;

        // opacitat assumida constant per a tot vòxel
        const float voxelOpacity = 0.011;

        // fem tantes iteracions com intervals per anar de tmin a tmax
        // amb un incrementa de deltaT cada vegada
        for (int i = 0; i < numIntervals; i++){

            // t de la iteració actual
            iterT = tmin + i * deltaT;

            // punt de mostreig
            iterPoint = r.pointAtParameter(iterT);

            // color del material isotròpic del volum al punt
            pointColor = (dynamic_cast<Isotropic*>(material))->getValue(iterPoint);

            // actualització de color i opacitat
            outColor = outColor + (1 - outOpacity) * voxelOpacity * pointColor;
            outOpacity += (1 - outOpacity) * voxelOpacity;

            // s'acaba de forma anticipada si s'assoleix l'opacitat màxima
            if (outOpacity >= 1) break;

        }

        // només es considerarà que hi ha hit si així es determina segons la
        // funció de distribució; es considera que hi ha hit si el càlcul de
        // distància de hit es considera inferior a la distància recorreguda
        // dins el volum
        float distance_inside_boundary = (tmax - tmin);
        float hit_distance = -(1/density)*(log(drand48()));

        if (hit_distance < distance_inside_boundary){

            // darrer punt (on l'opacitat ha arribat a 1, o el de tmax)
            info.p = iterPoint;

            info.t = iterT;

            info.mat_ptr = material;

            return true;
        }
    }

    return false;
}
