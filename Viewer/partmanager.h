#ifndef PARTMANAGER_H
#define PARTMANAGER_H
#include <vector>

class Part;

class PartManager
{
public:
	static PartManager* getInstance() { if(!instance) instance = new PartManager; return instance; }
	static void freeInstance() { if(instance) delete instance; }

	Part* newPart(bool subPart = false);
	void freePart(Part *p);

	void draw();
	void draw3();

private:
	static PartManager* instance;

	std::vector<Part*> parts;

	PartManager();
	PartManager(const PartManager&);
	PartManager& operator=(const PartManager&);
	~PartManager();
};

#endif // PARTMANAGER_H
