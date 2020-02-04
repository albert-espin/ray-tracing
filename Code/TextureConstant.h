#ifndef TEXTURECONSTANT_H
#define TEXTURECONSTANT_H

#include "Texture.h"

// Textura constant, d'un sol color
class TextureConstant : public Texture
{
public:
    TextureConstant(int dimX, int dimY, int dimZ, const vec3& color);
    virtual ~TextureConstant();

    vec3 value(const vec3 &p);

private:

    // color constant de la textura
    vec3 color;

};

#endif // TEXTURECONSTANT_H
