#include "material.h"
#include <GL/glew.h>

Material::Material() : ambient({0.0,0.0,0.0,1.0}), diffuse({0.0,0.0,0.0,1.0}),
    specular({0.0,0.0,0.0,1.0}),emission({0.0,0.0,0.0,1.0}),shininess(0.0)
{

}

Material::~Material()
{

}

void Material::apply() const
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}
