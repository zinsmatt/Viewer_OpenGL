#ifndef PART_H
#define PART_H
#include <cstdlib>
#include <vector>
#include "abstractpart.h"

class Mesh;
class Material;

class Part : public AbstractPart
{
	friend class PartManager;

protected:
	Mesh *mesh;
	float color[4];
	Material *material;

	Part(int id);
	virtual ~Part();

public:
	void setMesh(Mesh* m);
	Mesh* getMesh() { return mesh; }

	void setColor(float r, float g, float b) {	color[0] = r; color[1] = g; color[2] = b; }

	void applyMaterial();	//calls openGL function glMaterial()
	Material* getMaterial() { return material; }

	virtual void draw(Matrixh mat);
	virtual void draw3();
	virtual PART_TYPE getType() const { return PART_TYPE::PART_INSTANCE; }
	virtual void showInfo() const;

};

#endif // PART_H
