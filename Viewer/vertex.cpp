#include "vertex.h"
#include "vector.h"
#include "face.h"

void Vertex::computeNormal()
{
	Vector temp(0.0,0.0,0.0,1.0);
	for(int iter = 0; iter < adjacentFaces.size(); iter++)
	{
		Vector face_normal;
		adjacentFaces[iter]->getNormale(face_normal);
		temp += face_normal;
	}
	temp.normalize();
	nx = temp[0];
	ny = temp[1];
	nz = temp[2];
}
