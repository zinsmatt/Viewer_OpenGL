#ifndef PARTMANAGER_H
#define PARTMANAGER_H
#include <vector>

class Part;
class SnowMan;

class PartManager
{
public:
	static PartManager* getInstance() { if(!instance) instance = new PartManager; return instance; }
	static void freeInstance() { if(instance) delete instance; }

	Part* newPart(bool subPart = false);
	void freePart(Part *p);

	SnowMan* newSnowManPart(bool subPart = false);

	void draw();
	void draw3();

	std::vector<Part*>::iterator getStartIterator() { return parts.begin(); }
	std::vector<Part*>::iterator getEndIterator() { return parts.end(); }


private:
	static PartManager* instance;

	std::vector<Part*> parts;

	PartManager();
	PartManager(const PartManager&);
	PartManager& operator=(const PartManager&);
	~PartManager();
};

#endif // PARTMANAGER_H
