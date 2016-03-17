#ifndef ASSEMBLY_H
#define ASSEMBLY_H
#include "abstractpart.h"
#include <vector>

class Part;

class Assembly : public AbstractPart
{
protected:
	std::vector<AbstractPart*> subParts;

public:
	Assembly(int id);
	virtual ~Assembly();

	void addSubPart(AbstractPart *part);
	void removeSubPart(AbstractPart *part);

	virtual void draw(Matrixh mat);
	virtual void draw3();
	virtual AbstractPart::PART_TYPE getType() const { return AbstractPart::PART_TYPE::PART_ASSEMBLY; }
	virtual void showInfo() const;
};

#endif // ASSEMBLY_H
