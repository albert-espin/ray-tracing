#ifndef LIGHT_H
#define LIGHT_H

#include <vector>
#include "Ray.h"


// classe que representa una llum
class Light
{
public:

    Light(vec3& position, vec3& ambient, vec3& diffuse, vec3& specular, float a, float b, float c);

    virtual ~Light(){}

    // retorna la posició
    vec3 getPosition() const;

    // retorna el component ambient
    vec3 getAmbient() const;

    // retorna el component difús
    vec3 getDiffuse() const;

    // retorna el component especular
    vec3 getSpecular() const;


    // calcula el factor d'atenuació de la intensitat lumínica per a la distància passada
    float obtainAttenuationFactorAtDistance(float dist);

protected:

    // ubicació de la llum a l'espai
    vec3 position;

    // component ambient
    vec3 ambient;

    // component difús
    vec3 diffuse;

    // component especular
    vec3 specular;


    // paràmetre 'a' per calcular l'atenuació
    float attenuation_a;

    // paràmetre 'b' per calcular l'atenuació
    float attenuation_b;

    // paràmetre 'c' per calcular l'atenuació
    float attenuation_c;

};

#endif // LIGHT_H
