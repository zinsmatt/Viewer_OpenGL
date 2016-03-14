#include "meshmanager.h"
#include "mesh.h"
#include <iostream>
#include <cstdlib>

MeshManager* MeshManager::instance = NULL;

MeshManager::~MeshManager() {
	for(int iter = 0; iter<meshes.size(); ++iter)
	{
		delete meshes[iter];
	}
}

Mesh* MeshManager::newMesh()
{ // allocate a new mesh and keep a pointer for update
	Mesh* temp = new Mesh;
	meshes.push_back(temp);
	return temp;
}

void MeshManager::freeMesh(Mesh *mesh){
	for(int iter=0; iter<meshes.size(); iter++)
	{
		if(meshes[iter] == mesh)
		{
			meshes.erase(meshes.begin()+iter);
			delete mesh;
			return;
		}
	}
}
