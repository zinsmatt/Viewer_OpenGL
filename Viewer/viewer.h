#ifndef VIEWER_H
#define VIEWER_H
#include <cstdlib>
#include <ctime>
#include <string>
#include "point.h"
#include "matrixh.h"
#include "utility.h"

#define NB_COUL 50

class GLFWwindow;
class Mesh;
class Vertex;
class Face;

class Viewer
{

	enum class DRAW_MODE
	{
		WIREFRAME,
		TRIANGLES
	};

	enum class SMOOTH_MODE
	{
		NO_SMOOTH,
		SMOOTH
	};

	enum class LIGHTING_MODE
	{
		CONSTANT,
		GOURAUD
	};



public:
	static Viewer* getInstance(int w = 400, int h = 400 , const std::string& name = "Default Name"){
		if(!instance)
			instance = new Viewer(w,h,name);
		return instance;
	}
	static void freeInstace(){
		if(instance)
			delete instance;
	}

	void setColorIndex(int idx) { color_index = idx; }

	void update();
	void clear();

	bool isClosed() const { return close; }

	void drawFace(Face *face);
	void drawAxes(float size);

	void setPerspective(float fovy, float ratio, float znear, float zfar);
	void polarView(float distance, float azimut, float elevation, float twist);
	void translateCamera(float x, float y, float z);
	void reshape(int width, int height);
	void zoom(double x, double y);
	void mouse_button(int button, int action, int mods);
	void key(int key, int scancode, int action, int mods);

private:
	static Viewer* instance;

	Viewer(int width, int height, const std::string title);
	Viewer(const Viewer&);
	Viewer& operator=(const Viewer&);
	virtual ~Viewer();

	GLFWwindow *window;
	DRAW_MODE draw_mode;
	SMOOTH_MODE smooth_mode;
	LIGHTING_MODE lighting_mode;
	bool draw_normals;
	bool close;
	int color_index;
	float color_tab[15];
	int nb_faces;

	/* angles in degrees */
	float azimut;
	float elevation;
	float twist;
	float distance;
};

void reshape_callback(GLFWwindow* window, int width, int height);
void zoom_callback(GLFWwindow* window, double x, double y);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


#endif // VIEWER_H
