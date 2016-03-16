#ifndef PARTMANAGER_H
#define PARTMANAGER_H
#include <vector>

class AbstractPart;
class Part;
class Assembly;
class SnowMan;

class PartManager
{
public:
	static PartManager* getInstance() { if(!instance) instance = new PartManager; return instance; }
	static void freeInstance() { if(instance) delete instance; }

	Part* newPart(bool subPart = false);
	Assembly* newAssembly(bool subAssembly = false);
	SnowMan* newSnowManPart(bool subPart = false);
	void freeElement(AbstractPart *p);

	void draw();
	void draw3();

	void printSceneTree() const;

	std::vector<AbstractPart*>::iterator getStartIterator() { return parts.begin(); }
	std::vector<AbstractPart*>::iterator getEndIterator() { return parts.end(); }


private:
	static PartManager* instance;
	int lastId;

	std::vector<AbstractPart*> parts;

	PartManager();
	PartManager(const PartManager&);
	PartManager& operator=(const PartManager&);
	~PartManager();
};

#endif // PARTMANAGER_H
