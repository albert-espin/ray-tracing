#ifndef TEXTURE_H
#define TEXTURE_H

#include "Ray.h"

// Rpresentació de colors en una regió de l'espai
class Texture
{
public:

    Texture(int dimX, int dimY, int dimZ);
    ~Texture();

    virtual vec3 value(const vec3& p) = 0;

    // dimensions a l'espai
    int dimX, dimY, dimZ;
};

#endif // TEXTURE_H


