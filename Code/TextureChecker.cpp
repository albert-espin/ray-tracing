#include "TextureChecker.h"


TextureChecker::TextureChecker(int dimX, int dimY, int dimZ, const vec3 &colorA, const vec3 &colorB) : Texture(dimX, dimY, dimZ)
{
    this->colorA = colorA;
    this->colorB = colorB;
}

TextureChecker::~TextureChecker()
{

}

vec3 TextureChecker::value(const vec3 &p)
{
    // si una funció sobre el punt dóna resultat negatiu es retorna un color,
    // sinó, l'alternatiu
    float f = sin(10 * p.x) * sin(10 * p.y) * sin(10 * p.z);
    return (f > 0) ? colorA : colorB;
}
