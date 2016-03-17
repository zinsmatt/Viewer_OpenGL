#ifndef PART_H
#define PART_H
#include <cstdlib>
#include <vector>
#include "abstractpart.h"

class Mesh;

class Part : public AbstractPart
{
	friend class PartManager;

protected:
	Mesh *mesh;
	float color[4];

	Part(int id);
	virtual ~Part();

public:
	void setMesh(Mesh* m);
	Mesh* getMesh() { return mesh; }

	void setColor(float r, float g, float b) {	color[0] = r; color[1] = g; color[2] = b; }

	virtual void draw(Matrixh mat);
	virtual void draw3();
	virtual PART_TYPE getType() const { return PART_TYPE::PART_INSTANCE; }
	virtual void showInfo() const;

};

#endif // PART_H
