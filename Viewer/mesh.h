#ifndef MESH_H
#define MESH_H
#include "point.h"
#include "vertex.h"
#include <vector>
#include <iterator>

class Matrixh;

class Mesh
{
private:
	void subdivideTriangle(Point3f a, Point3f b, Point3f c, int n);
	std::vector<Vertex*> vertices;
	std::vector<Face*> faces;

public:

	Mesh();
	~Mesh();

	void addFace(Vertex *a, Vertex *b, Vertex *c);
	void addSquareFace(Vertex *a, Vertex *b, Vertex *c, Vertex *d, Vertex *center);

	Vertex* newVertex(float x, float y, float z);
	void computeNormals();

	void draw(Matrixh &transf);
	void draw3(Matrixh *transf);

	void createSphere(int step);
	void createCube(float x = 1.0, float y = 1.0, float z = 1.0);
	void createCone(int steps, float height = 1.0, float radius = 1.0);
};

#endif // MESH_H
