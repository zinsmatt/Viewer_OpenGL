#include "partmanager.h"
#include "part.h"
#include "assembly.h"
#include "snowman.h"
#include "matrixh.h"
#include <iostream>

PartManager* PartManager::instance = NULL;

PartManager::PartManager() : lastId(0)
{

}

PartManager::~PartManager()
{
	for(int i=0;i<parts.size();++i)
		delete parts[i];
}

Part* PartManager::newPart(bool subPart)
{
	/* if subPart = true, the part is not registered by the manager
	 the user have to take care of deallocation */

	Part *nouv = new Part(lastId++);
	if(subPart == false)
		parts.push_back(nouv);
	return nouv;
}

Assembly* PartManager::newAssembly(bool subAssembly)
{
	/* if subAssembly = true, the assembly is not registered by the manager
	 the user have to take care of deallocation */

	Assembly* nouv = new Assembly(lastId++);
	if(subAssembly== false)
		parts.push_back(nouv);
	return nouv;
}

SnowMan* PartManager::newSnowManPart(bool subPart)
{
	SnowMan* nouv = new SnowMan(lastId++);
	if(subPart == false)
		parts.push_back(nouv);
	return nouv;
}


void PartManager::freeElement(AbstractPart *p)
{
	for(int i=0;i<parts.size(); i++)
	{
		if(parts[i] == p)
		{
			AbstractPart* temp = parts[i];
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

void PartManager::printSceneTree() const
{
	std::cout << "\n================== Scene Tree ==================" << std::endl;
	for(int iter = 0; iter<parts.size(); ++iter)
	{
		parts[iter]->showInfo();
	}
	std::cout << "================================================\n\n";
}
