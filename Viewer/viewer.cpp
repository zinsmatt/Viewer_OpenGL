#include "viewer.h"
#include "vector.h"
#include "partmanager.h"
#include "part.h"
#include "snowman.h"
#include "face.h"
#include "vertex.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>


Viewer* Viewer::instance = NULL;


Viewer::Viewer(int width, int height, const std::string title) : window(NULL), close(false), color_index(0),
    nb_faces(0), azimut(0.0), elevation(0.0), twist(0.0), distance(0.0), draw_normals(false),
    draw_mode(DRAW_MODE::TRIANGLES), smooth_mode(SMOOTH_MODE::NO_SMOOTH), lighting_mode(LIGHTING_MODE::CONSTANT)
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

	std::cout << "width = " << width << std::endl;
	std::cout << "height = " << height << std::endl;

	glViewport(0,0,width,height);
	this->setPerspective(90,1.0,0.1,50);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	this->polarView(10,45,45,0);
	//gluLookAt(2,2,2,0,0,0,0,0,1);
	//glTranslatef(0.0,0.0,-10.0);

	/*float azimut = 45.0;
	float elevation = 45.0;
	float twist = 0.0;

	Matrixh mat1;
	mat1.setRotationZ(PI/2-TO_RADIANS(azimut));
	Matrixh mat2;
	mat2.setRotationX(-PI/2-TO_RADIANS(elevation));
	Matrixh mat3;	glfwTerminate();

	mat3.setRotationY(PI);
	Matrixh mat4;
	mat4.setTranslation(0.0,0.0,-10.0);

	//Matrixh res = mat1 * mat2 * mat3 * mat4;
	Matrixh res = mat4 * mat3 * mat2 * mat1;
	glMultMatrixf(res.toColMajorMatrix());
	std::cout << "mymatrix = " << res;
*/

	/*float temp[16];

	glTranslatef(0.0,0.0,-10.0);

	glRotatef(TO_DEGRES(PI),0.0,1.0,0.0);

	glGetFloatv(GL_MODELVIEW_MATRIX,temp);
	Matrixh mata;
	mata.fromColMajorMatrix(temp);
	std::cout << "gl matrix = " << mata;

	glLoadIdentity();

	glRotatef(TO_DEGRES(-PI/2)-elevation,1.0,0.0,0.0);

	glGetFloatv(GL_MODELVIEW_MATRIX,temp);
	Matrixh mat;
	mat.fromColMajorMatrix(temp);
	std::cout << "gl matrix = " << mat;
	std::cout << "cos(-3pi/4) = " << cos(TO_RADIANS(TO_DEGRES(-PI/2-PI/4))) << std::endl;

	glRotatef(TO_DEGRES(PI/2)-azimut,0.0,0.0,1.0);
*/


	/* ======test ==========
	float temp[16];
	glMatrixMode(GL_MODELVIEW_MATRIX);
	glLoadIdentity();
	glRotatef(45,1,0,0);
	glRotatef(45,0,1,0);
	glGetFloatv(GL_MODELVIEW_MATRIX,temp);
	print(temp);


	Matrixh mx;
	mx.setRotationX(TO_RADIANS(45));
	Matrixh my;
	my.setRotationY(TO_RADIANS(45));
	Matrixh mm = mx * my;
	std::cout << mm;

	 ------------------------- */



	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

// ---------------test lighting --------------


	//GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	//GLfloat mat_diffuse[] = { 0.9, 0.2, 0.1, 1.0 };
	//GLfloat mat_specular[] = { 0.9, 0.9, 0.9, 1.0 };
	//GLfloat mat_emission[] = { 0.0, 0.0, 0.0, 0.0};
	//
	//
    //glMaterialfv(GL_FRONT, GL_AMBIENT,mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    //glMaterialf(GL_FRONT, GL_SHININESS, 100.0);


	GLfloat light_ambient[] = {0.1,0.1,0.1,1.0};
	GLfloat light_diffuse[] = {0.9,0.9,0.9,1.0};
	GLfloat light_specular[] = {0.9,0.9,0.9,1.0};
	GLfloat light_position[] = {0,0,30,1};
	GLfloat light_direction[] = {0,0,-1,1};


	glLightfv(GL_LIGHT0,GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 10);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);


	glEnable(GL_LIGHT0);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);


	glfwSetInputMode(window,GLFW_STICKY_KEYS,GL_FALSE);
	glfwSetWindowUserPointer(window,this); //store this viewer

	// use C function as callback and they call instance methods
	glfwSetWindowSizeCallback(window,reshape_callback);
	glfwSetScrollCallback(window, zoom_callback);
	glfwSetMouseButtonCallback(window,mouse_button_callback);
	glfwSetKeyCallback(window, key_callback);


	/* ---- init colors ----- */
	color_tab[0] = 1.0;
	color_tab[1] = 0.0;
	color_tab[2] = 0.0;
	color_tab[3] = 1.0;
	color_tab[4] = 1.0;
	color_tab[5] = 1.0;
	color_tab[6] = 1.0;
	color_tab[7] = 1.0;
	color_tab[8] = 0.0;
	color_tab[9] = 0.0;
	color_tab[10] = 1.0;
	color_tab[11] = 1.0;
	color_tab[12] = 1.0;
	color_tab[13] = 0.0;
	color_tab[14] = 1.0;

}

Viewer::~Viewer()
{
	std::cout << "Destructor !! \n" << std::endl;
	glfwTerminate();
}

void Viewer::setPerspective(float fovy, float ratio, float znear, float zfar)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// fovy in degree
	float right = znear * tan(TO_RADIANS(fovy/2.0));
	float top = ratio * right;
	glFrustum(-right,right,-top,top,znear,zfar);
	glMatrixMode(GL_MODELVIEW_MATRIX);
}

void Viewer::polarView(float distance, float azimut, float elevation, float twist)
{/*
	this->azimut = azimut;
	this->elevation = elevation;
	this->twist = twist;
	this->distance = distance;
	// angles given in degrees
	glMatrixMode(GL_MODELVIEW_MATRIX);
	glLoadIdentity();
	Matrixh mat1;
	mat1.setRotationZ(PI/2-TO_RADIANS(azimut));
	Matrixh mat2;
	mat2.setRotationX(-PI/2-TO_RADIANS(elevation));
	Matrixh mat3;
	mat3.setRotationY(PI);
	Matrixh mat4;
	mat4.setTranslation(0.0,0.0,-distance);
	Matrixh mat5;
	mat5.setRotationZ(TO_RADIANS(twist));
	Matrixh res = mat5 * mat4 * mat3 * mat2 * mat1;
	glMultMatrixf(res.toColMajorMatrix());
*/

	this->azimut = azimut;
	this->elevation = elevation;
	this->twist = twist;
	this->distance = distance;
	// angles given in degrees
	glMatrixMode(GL_MODELVIEW_MATRIX);
	glLoadIdentity();

	glRotatef(twist,0,0,1);
	glTranslatef(0.0,0.0,-distance);
	glRotatef(180.0,0,1,0);
	glRotatef(-90-elevation,1,0,0);
	glRotatef(90-azimut,0,0,1);

	/* snowman follows observator */
	PartManager *manager = PartManager::getInstance();
	auto it = manager->getStartIterator();
	auto end = manager->getEndIterator();
	while(it != end)
	{
		if((*it)->getType() == AbstractPart::PART_TYPE::SNOWMAN_ASSEMBLY)
			dynamic_cast<SnowMan*>((*it))->moveHead(azimut, elevation);
		++it;
	}
}

void Viewer::reshape(int width, int height)
{
	std::cout << "Reshape \n";
    glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,((float)width/height),0.1,50);
	glMatrixMode(GL_MODELVIEW);
}

void Viewer::zoom(double x, double y)
{
	polarView(distance-y,azimut,elevation,twist);
}


void Viewer::mouse_button(int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		polarView(distance,azimut,elevation,twist+5);
	}else if(button == GLFW_MOUSE_BUTTON_LEFT)
	{
		polarView(distance,azimut,elevation,twist-5);
	}
}

void Viewer::key(int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		if (key == GLFW_KEY_UP)
			polarView(distance,azimut,elevation+5,twist);
		else if (key == GLFW_KEY_DOWN)
	        polarView(distance,azimut,elevation-5,twist);
		else if (key == GLFW_KEY_LEFT)
	        polarView(distance,azimut-5,elevation,twist);
		else if (key == GLFW_KEY_RIGHT)
	        polarView(distance,azimut+5,elevation,twist);
	}


	/* w ==> switch draw_mode : wireframe <-> triangles */
	if(action == GLFW_PRESS && key == GLFW_KEY_Z)
	{
		if(draw_mode == DRAW_MODE::WIREFRAME)
			draw_mode = DRAW_MODE::TRIANGLES;
		else if(draw_mode == DRAW_MODE::TRIANGLES)
			draw_mode = DRAW_MODE::WIREFRAME;
	}

	/* s ==> switch smooth mode : smooth <-> no smooth */
	if(action == GLFW_PRESS && key == GLFW_KEY_S)
	{
		if(smooth_mode == SMOOTH_MODE::SMOOTH)
			smooth_mode = SMOOTH_MODE::NO_SMOOTH;
		else
			smooth_mode = SMOOTH_MODE::SMOOTH;
	}

	/* l ==> siwth lighting mode : constant <-> gouraud */
	if(action == GLFW_PRESS && key == GLFW_KEY_L)
	{
		if(lighting_mode == LIGHTING_MODE::CONSTANT)
		{
			lighting_mode = LIGHTING_MODE::GOURAUD;
			glShadeModel(GL_SMOOTH);
			std::cout << "switch to gouraud illumination" << std::endl;
		}else
		{
			lighting_mode = LIGHTING_MODE::CONSTANT;
			glShadeModel(GL_FLAT);
			std::cout << "switch to constant illumination model" << std::endl;
		}
	}

	/* n ==> switch draw normals on/off */
	if(action == GLFW_PRESS && key == GLFW_KEY_N)
	{
		draw_normals = !draw_normals;
	}
}

void Viewer::drawAxes(float size)
{
	glBegin(GL_LINES);
	glColor3f(1.0,0.0,0.0);
	glVertex3f(size,0.0,0.0);
	glVertex3f(0.0,0.0, 0.0);
	glColor3f(0.0,1.0,0.0);
	glVertex3f(0.0,size,0.0);
	glVertex3f(0.0,0.0, 0.0);
	glColor3f(0.0,0.0,1.0);
	glVertex3f(0.0,0.0,size);
	glVertex3f(0.0,0.0,0.0);
	glEnd();
}

void Viewer::update()
{
	clear();
	nb_faces = 0;
	this->drawAxes(2.0);

	PartManager::getInstance()->draw();
	//std::cout << "Nb Faces : " << nb_faces << std::endl;

	glfwSwapBuffers(window);
	glfwPollEvents();

	if(glfwWindowShouldClose(window))
		close = true;
}

void Viewer::clear()
{
	glClearColor(0.0f,0.78f,0.5f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Viewer::drawFace(Face* face)
{
	Vertex *a = face->v1;
	Vertex *b = face->v2;
	Vertex *c = face->v3;

	if(draw_mode == DRAW_MODE::WIREFRAME)
		glBegin(GL_TRIANGLES);
	else if(draw_mode == DRAW_MODE::TRIANGLES)
		glBegin(GL_LINE_LOOP);

	if(smooth_mode == SMOOTH_MODE::NO_SMOOTH)
	{
		Vector norm;
		face->getNormale(norm);
		glNormal3f(norm[0],norm[1],norm[2]);
		glVertex3f(a->x,a->y,a->z);
		glVertex3f(b->x,b->y,b->z);
		glVertex3f(c->x,c->y,c->z);
	}else if (smooth_mode == SMOOTH_MODE::SMOOTH)
	{
		glNormal3f(a->nx,a->ny,a->nz);
		glVertex3f(a->x,a->y,a->z);

		glNormal3f(b->nx,b->ny,b->nz);
		glVertex3f(b->x,b->y,b->z);

		glNormal3f(c->nx,c->ny,c->nz);
		glVertex3f(c->x,c->y,c->z);

		/*Vector v(a->x,a->y,a->z,1.0);
		v.normalize();
		glNormal3f(v[0],v[1],v[2]);
		glVertex3f(a->x,a->y,a->z);

		v.set(b->x,b->y,b->z,1.0);
		v.normalize();
		glNormal3f(v[0],v[1],v[2]);
		glVertex3f(b->x,b->y,b->z);

		v.set(c->x,c->y,c->z,1.0);
		v.normalize();
		glNormal3f(v[0],v[1],v[2]);
		glVertex3f(c->x,c->y,c->z);*/
	}

	glEnd();


	if( draw_normals == true)
	{
		glBegin(GL_LINES);
		if(smooth_mode == SMOOTH_MODE::NO_SMOOTH)
		{
			Vector norm;
			face->getNormale(norm);
			glVertex3f(a->x,a->y,a->z);
			glVertex3f(a->x+norm[0],a->y+norm[1],a->z+norm[2]);

			glVertex3f(b->x,b->y,b->z);
			glVertex3f(b->x+norm[0],b->y+norm[1],b->z+norm[2]);

			glVertex3f(c->x,c->y,c->z);
			glVertex3f(c->x+norm[0],c->y+norm[1],c->z+norm[2]);
		}else if(smooth_mode == SMOOTH_MODE::SMOOTH)
		{
			Vector norm;
			face->getNormale(norm);
			glVertex3f(a->x,a->y,a->z);
			glVertex3f(a->x+a->nx,a->y+a->ny,a->z+a->nz);

			glVertex3f(b->x,b->y,b->z);
			glVertex3f(b->x+b->nx,b->y+b->ny,b->z+b->nz);

			glVertex3f(c->x,c->y,c->z);
			glVertex3f(c->x+c->nx,c->y+c->ny,c->z+c->nz);
		}
		glEnd();
	}
	nb_faces += 1;
}


void reshape_callback(GLFWwindow *window, int width, int height)
{
	static_cast<Viewer*>(glfwGetWindowUserPointer(window))->reshape(width,height);
}

void zoom_callback(GLFWwindow *window, double x, double y)
{
	static_cast<Viewer*>(glfwGetWindowUserPointer(window))->zoom(x,y);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	static_cast<Viewer*>(glfwGetWindowUserPointer(window))->mouse_button(button, action, mods);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	static_cast<Viewer*>(glfwGetWindowUserPointer(window))->key(key, scancode ,action, mods);
}
