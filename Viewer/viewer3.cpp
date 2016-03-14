#include "viewer3.h"
#include <iostream>
#include <GLFW/glfw3.h>

Viewer3* Viewer3::instance = NULL;



Viewer3::Viewer3(int width, int height, const std::string title) : window(NULL), close(false),
    vertexArrayId(0)
{
	std::cout << "Constructor !!\n" << std::endl;
	if(!glfwInit())
	{
		std::cerr << "Error initialisaing GLFW" << std::endl;
		return ;
	}

	window = glfwCreateWindow(width, height,title.c_str(), NULL, NULL);

	if(!window)
	{
		std::cerr << "Error creating window" << std::endl;
		glfwTerminate();
		return ;
	}

	glfwMakeContextCurrent(window);

	GLenum state = glewInit();
	if(state != GLEW_OK)
	{
		std::cerr<<"Error initializing OpenGL" << std::endl;
		return ;
	}

	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,1.0,0.1,50);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(0.0,0.0,-2.0);
	//this->polarView(10,45,45,0);
	gluLookAt(2,2,2,0,0,0,0,0,1);
	//glTranslatef(0.0,0.0,-10.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

Viewer3::~Viewer3()
{
	glfwTerminate();
}

void Viewer3::clear()
{
	glClearColor(0.2,0.7,0.1,1.0);
	glClear(GL_COLOR_BUFFER_BIT	| GL_DEPTH_BUFFER_BIT);
}

void Viewer3::update()
{
	clear();
	draw();
	glfwSwapBuffers(window);

	glfwPollEvents();
	if(glfwWindowShouldClose(window))
		close = true;
}

void Viewer3::draw()
{
	GLfloat vertices[] = {-0.5,0.5,0.5,
	                      -0.5,0.5,-0.5,
	                      0.5,0.5,-0.5,
	                      0.5,0.5,0.5,
						-0.5,-0.5,0.5,
						-0.5,-0.5,-0.5,
						0.5,-0.5,-0.5,
						0.5,-0.5,0.5};

	GLubyte indices[] = {0,1,2, 2,3,0,   // 36 of indices
	                     0,3,4, 4,5,0,
	                     0,5,6, 6,1,0,
	                     1,6,7, 7,2,1,
	                     7,4,3, 3,2,7,
	                     4,7,6, 6,5,4};

	glColor3f(0.0,0.0,1.0);

	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3,GL_FLOAT,0,vertices);
	glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_VERTEX_ARRAY);
}
