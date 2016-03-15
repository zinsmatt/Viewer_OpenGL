#ifndef PART_H
#define PART_H
#include <cstdlib>
#include <vector>
#include "matrixh.h"

class Mesh;

class Part
{
	friend class PartManager;

protected:
	Mesh *mesh;
	Matrixh *matrix;
	std::vector<Part*> subParts;
	float color[4];

	Part(Mesh* m=NULL);
	virtual ~Part();

public:

	void setMesh(Mesh* m);
	void createEmptyMesh();
	Mesh* getMesh() { return mesh; }

	void setMatrix(Matrixh *mat);
	void setMatrix(const Matrixh& mat);
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
