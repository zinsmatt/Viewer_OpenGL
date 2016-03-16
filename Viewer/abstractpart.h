#ifndef ABSTRACTPART_H
#define ABSTRACTPART_H

class Matrixh;

enum PART_TYPE
{
	PART_INSTANCE,
	PART_ASSEMBLY,
	SNOWMAN_ASSEMBLY
};

class AbstractPart
{
	friend class PartManager;
protected:
	Matrixh *matrix;
	int id;

public:
	AbstractPart(int id);
	virtual ~AbstractPart();

	void setMatrix(const Matrixh& mat);
	Matrixh* getMatrix() { return matrix; }

	virtual void draw(Matrixh mat) = 0;
	virtual void draw3() = 0;
	virtual PART_TYPE getType() const = 0;
	virtual void showInfo() const = 0;
};

#endif // ABSTRACTPART_H
