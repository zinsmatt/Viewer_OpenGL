#include <GL/glew.h>
#include "part.h"
#include "meshmanager.h"
#include "mesh.h"
#include "viewer.h"
#include "material.h"

Part::Part(int id) : AbstractPart(id), material(new Material)
{
	color[0] = color[1] = color[2] = color[3] = 1.0;
	mesh = MeshManager::getInstance()->newMesh();
}

Part::~Part()
{	
	delete material;
	//do not delete the mesh because can be shared between several parts
}

void Part::setMesh(Mesh *m)
{
	if(mesh != NULL)
	{
		delete mesh;
	}
	mesh = m;
}


void Part::draw(Matrixh mat)
{
	Matrixh current = mat * (*matrix);
	if(mesh != NULL)
	{
		//glColor3f(color[0],color[1],color[2]);
		material->apply();
		mesh->draw(current);
	}
}

void Part::draw3()
{
	mesh->draw3(matrix);
}

void Part::showInfo() const
{
	std::cout << "Part " << id << std::endl;
}

void Part::applyMaterial()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, material->getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material->getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, material->getSpecular());
	glMaterialfv(GL_FRONT, GL_EMISSION, material->getEmission());
    glMaterialf(GL_FRONT, GL_SHININESS, material->getShininess());
}
