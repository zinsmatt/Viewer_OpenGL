#include "partmanager.h"
#include "part.h"

PartManager* PartManager::instance = NULL;

PartManager::PartManager()
{

}

PartManager::~PartManager()
{
	for(int i=0;i<parts.size();++i)
		delete parts[i];
}

Part* PartManager::newPart(bool subPart)
{
	Part *nouv = new Part;
	if(subPart == false)
		parts.push_back(nouv);
	return nouv;
}

void PartManager::freePart(Part *p)
{
	for(int i=0;i<parts.size(); i++)
	{
		if(parts[i] == p)
		{
			Part* temp = parts[i];
			parts.erase(parts.begin()+i);
			delete temp;
			return;
		}
	}
}

void PartManager::draw()
{
	for(int iter = 0; iter<parts.size(); ++iter)
	{
		parts[iter]->draw(Matrixh());
	}
}

void PartManager::draw3()
{
	for(int iter = 0; iter<parts.size(); ++iter)
	{
		parts[iter]->draw3();
	}
}
