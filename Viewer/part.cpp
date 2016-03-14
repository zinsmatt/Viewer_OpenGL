#include <GL/glew.h>
#include "part.h"
#include "meshmanager.h"
#include "matrixh.h"
#include "mesh.h"
#include "viewer.h"
Part::Part(Mesh* m)
{
	color[0] = color[1] = color[2] = 1.0;
	color[3] = 1;
	matrix = new Matrixh;
	if(m != NULL)
		mesh = m;
	else
		mesh = MeshManager::getInstance()->newMesh();
}

Part::~Part()
{
	if(matrix) delete matrix;
	for(int iter = 0; iter<subParts.size(); ++iter)
	{
		delete subParts[iter];
	}
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

void Part::setMatrix(Matrixh *mat)
{
	if(matrix != NULL)
	{
		delete matrix;
	}
	matrix = mat;
}

void Part::addSubPart(Part *part)
{
	subParts.push_back(part);
}

void Part::removeSubPart(Part *part)
{
	for(int iter=0;iter<subParts.size(); iter++)
		if(subParts[iter] == part)
		{
			Part* temp = subParts[iter];
			subParts.erase(subParts.begin()+iter);
			delete temp;
			return;
		}
}

void Part::draw(Matrixh mat)
{
	Matrixh current = mat * (*matrix);
	if(mesh != NULL)
	{
		glColor3f(color[0],color[1],color[2]);
		mesh->draw(current);
	}
	for(int iter = 0;iter < subParts.size(); ++iter)
		subParts[iter]->draw(current);
}

void Part::draw3()
{
	mesh->draw3(matrix);
}
