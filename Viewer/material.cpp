#include "material.h"

Material::Material() : ambient({0.0,0.0,0.0,1.0}), diffuse({0.0,0.0,0.0,1.0}),
    specular({0.0,0.0,0.0,1.0}),emission({0.0,0.0,0.0,1.0}),shininess(0.0)
{

}

Material::~Material()
{

}
