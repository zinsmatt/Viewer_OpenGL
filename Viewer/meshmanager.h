#ifndef MESHMANAGER_H
#define MESHMANAGER_H
#include <vector>

class Mesh;

class MeshManager
{
private:
	std::vector<Mesh*> meshes;

	static MeshManager* instance;

	MeshManager(const MeshManager&);
	MeshManager& operator=(const MeshManager&);
	MeshManager() {}
	~MeshManager();

public:
	static MeshManager* getInstance(){
		if(!instance)
			instance = new MeshManager;
		return instance;
	}

	static void freeInstance(){
		if(instance) delete instance;
	}


	Mesh* newMesh();
	void freeMesh(Mesh* mesh);
};

#endif // MESHMANAGER_H
