#ifndef VERTEX_H
#define VERTEX_H
#include <vector>

class Face;

class Vertex
{
private:
	std::vector<Face*> adjacentFaces;

public:
	Vertex(float _x, float _y, float _z, float _nx=0.0, float _ny=0.0, float _nz=0.0):
	    x(_x),y(_y),z(_z),nx(_nx),ny(_ny),nz(_nz) {}
	~Vertex() {}

	void addAdjacentFace(Face* face) { adjacentFaces.push_back(face); }
	void computeNormal();

	// cooridnates
	float x;
	float y;
	float z;

	// vertex normal
	float nx;
	float ny;
	float nz;
};

#endif // VERTEX_H
