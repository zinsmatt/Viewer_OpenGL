#include <iostream>
#include <vector>
#include "viewer.h"
#include "viewer3.h"
#include "mesh.h"
#include "meshmanager.h"
#include "partmanager.h"
#include "part.h"
using namespace std;

int main()
{
	std::srand(time(NULL));


	//MeshManager *manager = MeshManager::getInstance();
	PartManager *manager = PartManager::getInstance();

	Part *sphere = manager->newPart(false);
	sphere->getMesh()->createSphere(5);

	Mesh *sphereMesh = sphere->getMesh();

	std::vector<Part*> ballons;
	for(int iter=0;iter<50;iter++)
	{
		ballons.push_back(manager->newPart(false));
		ballons[ballons.size()-1]->setMesh(sphereMesh);
		ballons[ballons.size()-1]->getMatrix()->setTranslation(-5+rand()%10,-5+rand()%10,-5+rand()%10);
	}


	Part *cube = manager->newPart();
	cube->getMesh()->createCube();
	cube->getMatrix()->setTranslation(2.0,2.0,0.0);



	Viewer *viewer = Viewer::getInstance(600,600,"Viewer 3D");
//	viewer->clear();

	while(!viewer->isClosed())
	{
		viewer->update();
	}

	/*Viewer3 *viewer3 = Viewer3::getInstance(600,600,"Viewer 3D Opengl 3");
	viewer3->draw();
	while(!viewer3->isClosed())
	{
		viewer3->update();
	}*/


	//MeshManager::freeInstance();
	PartManager::freeInstance();
	Viewer::freeInstace();
	Viewer3::freeInstace();
	return 0;

	/*
    GLFWwindow *window;
    if(!glfwInit())
    {
        cerr << "Error initialising GLFW" << endl;
        return -1;
    }

    window = glfwCreateWindow(640,480,"Viewer",NULL,NULL);
    if(!window)
    {
        cerr << "Error creating window " << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while(!glfwWindowShouldClose(window))
    {
        // Render here

        // Swap buffers
        glfwSwapBuffers(window);

        // Get events
        glfwPollEvents();
    }


    glfwTerminate();

    return 0;

	*/
}

