#ifndef PART_H
#define PART_H
#include <cstdlib>
#include <vector>
#include "matrixh.h"

class Mesh;

class Part
{
private:
	Mesh *mesh;
	Matrixh *matrix;
	std::vector<Part*> subParts;
	float color[4];

public:
	Part(Mesh* m=NULL);
	~Part();

	void setMesh(Mesh* m);
	Mesh* getMesh() { return mesh; }

	void setMatrix(Matrixh *mat);
	Matrixh* getMatrix() { return matrix; }

	void addSubPart(Part* part);
	void removeSubPart(Part* part);

	void draw(Matrixh mat);
	void draw3();

	void setColor(float r, float g, float b) {
		color[0] = r; color[1] = g; color[2] = b;
	}
};

#endif // PART_H
