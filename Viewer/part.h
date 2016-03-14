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
};

#endif // PART_H
