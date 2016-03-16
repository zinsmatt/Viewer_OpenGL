#include "assembly.h"
#include "matrixh.h"

Assembly::Assembly(int id) : AbstractPart(id)
{

}

Assembly::~Assembly()
{
	for(int iter=0; iter<subParts.size(); iter++)
		delete subParts[iter];
}

void Assembly::addSubPart(AbstractPart *part)
{
	subParts.push_back(part);
}

void Assembly::removeSubPart(AbstractPart *part)
{
	for(int iter=0;iter<subParts.size(); iter++)
	{
		if(subParts[iter] == part)
		{
			AbstractPart* temp = subParts[iter];
			subParts.erase(subParts.begin()+iter);
			delete temp;
			return;
		}
	}
}

void Assembly::draw(Matrixh mat)
{
	Matrixh current = mat * (*matrix);
	for(int iter = 0;iter < subParts.size(); ++iter)
		subParts[iter]->draw(current);
}

void Assembly::draw3()
{

}
