#include "mesh.h"
#include "viewer.h"
#include "face.h"
#include <iostream>
#include <GL/glew.h>

Mesh::Mesh() //: matrix(NULL)
{
	//matrix = new Matrixh;
}

Mesh::~Mesh()
{
	for(int iter = 0; iter<vertices.size(); ++iter)
		delete vertices[iter];
	for(int iter = 0;iter<vertices.size(); ++iter)
		delete faces[iter];
}

void Mesh::addFace(Vertex* a, Vertex *b, Vertex *c)
{	// add a triangle face
	faces.push_back(new Face(a,b,c));
}

void Mesh::addSquareFace(Vertex* a, Vertex* b, Vertex *c, Vertex *d)
{	// add a square face decomposed in two triangles
	addFace(a,b,c);
	addFace(c,d,a);
}

Vertex* Mesh::newVertex(float x, float y, float z)
{
	Vertex* nouv_vertex = new Vertex({x, y, z, 0.0, 0.0, 0.0});
	vertices.push_back(nouv_vertex);
	return nouv_vertex;
}

void Mesh::computeNormals()
{
	for(int iter = 0; iter < vertices.size(); ++iter)
	{
		vertices[iter]->computeNormal();
	}
}

void Mesh::draw(Matrixh& transf)
{
	glPushMatrix();
	glMultMatrixf(transf.toColMajorMatrix());

	Viewer* viewer = Viewer::getInstance();
	for(int iter = 0; iter<faces.size(); ++iter)
	{
		Face* face = faces[iter];
		viewer->drawFace(face);
	}

	glPopMatrix();
}

void Mesh::draw3(Matrixh *transf)
{
	std::cout << "draw mesh in opengl version 3 " << std::endl;
}

void Mesh::createSphere(int step)
{
	coordinates.clear();

	//Point3f a = {0.0f ,1.0f ,0.0f};
	//Point3f b = {-0.75f, -0.5f, -0.43f};
	//Point3f c = { 0.75f, -0.5f, -0.43f};
	//Point3f d = {0.0f, -0.5f, 0.86f};

	Point3f a = {0.0f ,0.0f ,1.0f};
	Point3f b = {0.0f, 0.942809f, -0.333333f};
	Point3f c = { 0.816497f, -0.471405f, -0.333333f};
	Point3f d = {-0.816497f, -0.471405f, -0.333333f};

	// callsubdiv
	subdivideTriangle(a,b,c,step);
	subdivideTriangle(a,c,d,step);
	subdivideTriangle(a,d,b,step);
	subdivideTriangle(b,d,c,step);

	this->computeNormals();
}

void Mesh::subdivideTriangle(Point3f a, Point3f b, Point3f c, int n)
{
	if(n==0)
	{
		Vertex *v1 = newVertex(a[0],a[1],a[2]);
		Vertex *v2 = newVertex(b[0],b[1],b[2]);
		Vertex *v3 = newVertex(c[0],c[1],c[2]);
		this->addFace(v1, v2, v3);
	}else
	{
		Point3f ab,bc,ac;
		for(int i=0;i<3;i++)
		{
			ab[i] = (a[i] + b[i]) / 2;
			bc[i] = (b[i] + c[i]) / 2;
			ac[i] = (a[i] + c[i]) / 2;
		}
		normalise(ab);
		normalise(bc);
		normalise(ac);

		subdivideTriangle(a,ab,ac,n-1);
		subdivideTriangle(ab,b,bc,n-1);
		subdivideTriangle(ab,bc,ac,n-1);
		subdivideTriangle(bc,c,ac,n-1);
	}
}

void Mesh::createCube(float x, float y, float z)
{
	// create a cube centered on the origin with dimensions x, y and z along each axis
	vertices.reserve(8);
	x *= 0.5;
	y *= 0.5;
	z *= 0.5;

	Vertex *a = newVertex(-x,y, z);
	Vertex *b = newVertex(-x,y,-z);
	Vertex *c = newVertex( x,y,-z);
	Vertex *d = newVertex( x,y, z);
	Vertex *e = newVertex(-x,-y, z);
	Vertex *f = newVertex(-x,-y,-z);
	Vertex *g = newVertex( x,-y,-z);
	Vertex *h = newVertex( x,-y, z);

	this->addSquareFace(a,b,c,d);
	this->addSquareFace(d,c,g,h);
	this->addSquareFace(h,g,f,e);
	this->addSquareFace(e,f,b,a);
	this->addSquareFace(e,a,d,h);
	this->addSquareFace(b,f,g,c);

	this->computeNormals();
}

void Mesh::createCone(int steps, float height, float radius)
{
	/* create a cone with the base on the plan xOy */
	float increment_angle = 2*PI / steps;
	float angle = increment_angle;
	float x,y;

	Vertex *origin = newVertex(0.0,0.0,0.0);
	Vertex *A = newVertex(radius,0.0,0.0);
	Vertex *first_vertex = A;
	Vertex *prev_A;
	Vertex *head = newVertex(0.0,0.0,height);

	for(int iter = 0; iter < steps-1; iter++)
	{
		prev_A = A;
		x = radius * cos(angle);
		y = radius * sin(angle);
		A = newVertex(x,y,0.0);
		addFace(prev_A,origin,A);
		addFace(A, head, prev_A);
		angle += increment_angle;
	}
	// for the last face we loop to the first
	addFace(A,origin,first_vertex);
	addFace(first_vertex,head,A);

	this->computeNormals();
}

