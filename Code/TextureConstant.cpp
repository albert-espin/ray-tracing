#include "TextureConstant.h"





TextureConstant::TextureConstant(int dimX, int dimY, int dimZ, const vec3 &color) : Texture(dimX, dimY, dimZ)
{
    this->color = color;
}

TextureConstant::~TextureConstant()
{

}

vec3 TextureConstant::value(const vec3 &p)
{
    // el valor és constant per a tots els punts
    return color;
}
