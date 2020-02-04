#ifndef TEXTURECHECKER_H
#define TEXTURECHECKER_H

#include "Texture.h"

// Textura checker (simula un taulell d'escacs en alternar dos colors)
class TextureChecker : public Texture
{

public:
    TextureChecker(int dimX, int dimY, int dimZ, const vec3& colorA, const vec3& colorB);
    virtual ~TextureChecker();

    vec3 value(const vec3 &p);

private:

    // colors alternants de la textura
    vec3 colorA;
    vec3 colorB;
};

#endif // TEXTURECHECKER_H
