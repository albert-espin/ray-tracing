#include "Cube.h"



Cube::Cube(vec3 b0, vec3 b1, Material *m) : Object(m)
{
    minBound = b0;
    maxBound = b1;
}


bool Cube::hit(const Ray &r, float t_min, float t_max, HitInfo &rec) const
{
        float tmin = 0, tmax = 0;

        // detectem si hi ha impacte amb el cub; en tal cas el mètode hitMinMax
        // ens retorna les T dels punts de màxima i mínima intersecció; ens quedarem
        // amb el mínim, ja que és el més proper a l'origen del raig
        if (hitMinMax(r, t_min, t_max, tmin, tmax)){

            // la t d'impacte és la t mínima de les dues possibles
            rec.t = tmin;

            // el punt d'impacte el trobem amb el factor t i l'equació del raig
            vec3 intersectionPoint = r.pointAtParameter(rec.t);
            rec.p = intersectionPoint;

            // càlcul de la normal al punt
            rec.normal = this->obtainNormalAtIntersectionPoint(intersectionPoint);

            rec.mat_ptr = material;

            return true;
        }

        return false;
}


bool Cube::hitMinMax(const Ray &r, float t_min, float t_max, float &tmin, float &tmax) const
{
    vec3 rayOrigin = r.initialPoint();
    vec3 rayDir = r.dirVector();

    // obtenim els tmin i tmax "locals" per a col·lisions amb el cub (després
    // mirarem si estan al rang [t_min, t_max] del raig)
    tmin = (minBound.x - rayOrigin.x) / rayDir.x;
    tmax = (maxBound.x - rayOrigin.x) / rayDir.x;

    // si el mínim és major que el màxim, cal invertir-los
    if (tmin > tmax){
        float temp = tmin;
        tmin = tmax;
        tmax = temp;
    }

    // trobem les t locals per l'eix y
    float tymin = (minBound.y - rayOrigin.y) / rayDir.y;
    float tymax = (maxBound.y - rayOrigin.y) / rayDir.y;

    // si el mínim és major que el màxim, cal invertir-los
    if (tymin > tymax){
        float temp = tymin;
        tymin = tymax;
        tymax = temp;
    }

    // descartem poder tenir cap col·lisió si les t de l'eix y excedeixen
    // les t generals
    if ((tmin > tymax) || (tymin > tmax))
        return false;

    // adaptem la tmin com a tymin si la supera
    if (tymin > tmin)
        tmin = tymin;

    // adaptem la tmax com a tymax si és inferior
    if (tymax < tmax)
        tmax = tymax;

    // trobem les t locals per l'eix z
    float tzmin = (minBound.z - rayOrigin.z) / rayDir.z;
    float tzmax = (maxBound.z - rayOrigin.z) / rayDir.z;

    // si el mínim és major que el màxim, cal invertir-los
    if (tzmin > tzmax){
        float temp = tzmin;
        tzmin = tzmax;
        tzmax = temp;
    }

    // descartem poder tenir cap col·lisió si les t de l'eix z excedeixen
    // les t generals
    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    // adaptem la tmin com a tzmin si la supera
    if (tzmin > tmin)
        tmin = tzmin;

    // adaptem la tmax com a tzmax si és inferior
    if (tzmax < tmax)
        tmax = tzmax;

    // mirem que el rang de t locals del cub sigui tal que el raig pugui
    // veure els punts d'intersecció amb el cub
    if (t_min > tmin){
        tmin = tmax;

        if (tmax < t_max){
            return false;
        }
    }

    return true;
}

vec3 Cube::obtainNormalAtIntersectionPoint(vec3 intersectionPoint) const
{

    vec3 normal;

    // calculem el centre del cub com el punt mig a l'espai entre els dos punts
    // extrems
    vec3 cubeCenter = (maxBound + minBound) / 2.f;

    // definim el vector resultant d'anar del centre del cub al punt d'intersecció
    vec3 centerToInterVect = intersectionPoint - cubeCenter;

    // definim la longitud de costat del cub: la podem obtenir a partir com el valor
    // absolut de la resta de qualsevol de les coordenades (x, y o z) del cub, ja que
    // per definició un cub té totes les arestes de la mateixa longitud
    // NOTA: calculem les longituds en els tres eixos per si en el futur volem escalar
    // el cub en alguna direcció sense fer malbé el càlcul de les normals
    float cubeSide = std::abs(maxBound.x - minBound.x);

    // tot seguit busquem l'eix en què el desplaçament d'anar del centre del cub en
    // aquell eix restat a la longitud de costat del cub és menor: aquest eix defineix
    // la normal al punt d'intersecció, sent el signe determinat per si el desplaçament
    // esmentat es realitza en el sentit positiu o negatiu de l'eix

    float minDist = std::numeric_limits<float>::max();
    float dist = std::abs(cubeSide - std::abs(centerToInterVect.x));
    if (dist < minDist) {
        minDist = dist;
        normal = vec3(1, 0, 0);
        normal *= sign(centerToInterVect.x);
    }

    dist = std::abs(cubeSide - std::abs(centerToInterVect.y));
    if (dist < minDist) {
        minDist = dist;
        normal= vec3(0, 1, 0);
        normal *= sign(centerToInterVect.y);
    }

    dist = std::abs(cubeSide - std::abs(centerToInterVect.z));
    if (dist < minDist) {
        minDist = dist;
        normal = vec3(0, 0, 1);
        normal *= sign(centerToInterVect.z);
    }

    return normal;
}





