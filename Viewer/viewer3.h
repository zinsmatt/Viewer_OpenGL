#ifndef VIEWER3_H
#define VIEWER3_H
#include <GL/glew.h>
#include "utility.h"
#include <cstdlib>
#include <string>

class GLFWwindow;
class Mesh;

class Viewer3
{
public:
	static Viewer3* getInstance(int w = 400, int h = 400 , const std::string& name = "Default Name"){
		if(!instance)
			instance = new Viewer3(w,h,name);
		return instance;
	}


	static void freeInstace(){
		if(instance)
			delete instance;
	}

	bool isClosed() const { return close; }

	void update();
	void draw();
	void clear();

private:
	static Viewer3 *instance;

	Viewer3(int width, int height, const std::string title);
	Viewer3(const Viewer3&);
	Viewer3& operator=(const Viewer3&);
	~Viewer3();

	GLFWwindow *window;
	bool close;

	GLuint vertexArrayId;
};

#endif // VIEWER3_H
