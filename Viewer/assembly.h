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
	Assembly();
	virtual ~Assembly();

	void addSubPart(AbstractPart *part);
	void removeSubPart(AbstractPart *part);

	virtual void draw(Matrixh mat);
	virtual void draw3();
	virtual PART_TYPE getType() const { return PART_ASSEMBLY; }
};

#endif // ASSEMBLY_H