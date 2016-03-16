#include <GL/glew.h>
#include "part.h"
#include "meshmanager.h"
#include "mesh.h"
#include "viewer.h"

Part::Part(Mesh* m) : mesh(NULL)
{
	color[0] = color[1] = color[2] = color[3] = 1.0;
	if(m != NULL)
		mesh = m;
}

Part::~Part()
{	
	//do not delete the mesh because can be shared between several parts
}

void Part::createEmptyMesh()
{
	mesh = MeshManager::getInstance()->newMesh();
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
		glColor3f(color[0],color[1],color[2]);
		mesh->draw(current);
	}
}

void Part::draw3()
{
	mesh->draw3(matrix);
}
