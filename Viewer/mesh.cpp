#include "mesh.h"
#include "viewer.h"
#include <iostream>
#include <GL/glew.h>

Mesh::Mesh() //: matrix(NULL)
{
	//matrix = new Matrixh;
}

Mesh::~Mesh()
{
	//delete matrix;
}


void Mesh::addFace(Point3f a, Point3f b, Point3f c)
{	// add a triangle face
	coordinates.reserve(9);
	for(int i=0;i<3;++i)
		coordinates.push_back(a[i]);
	for(int i=0;i<3;++i)
		coordinates.push_back(b[i]);
	for(int i=0;i<3;++i)
		coordinates.push_back(c[i]);
}


void Mesh::addSquareFace(Point3f a, Point3f b, Point3f c, Point3f d)
{	// add a square face decomposed in two triangles
	addFace(a,b,c);
	addFace(c,d,a);
}


void Mesh::draw(Matrixh& transf)
{
	glPushMatrix();
	glMultMatrixf(transf.toColMajorMatrix());
	Point3f pt[3];
	Viewer* viewer = Viewer::getInstance();
	//viewer->setColorIndex(0);
	int nb = 0, iter = 0;
	while(iter < coordinates.size())
	{
		if(nb<3)
		{
			for(int i=0;i<3;i++)
				pt[nb][i] = coordinates[iter++];
			++nb;
		}
		if(nb == 3)
		{
			nb = 0;
			viewer->drawFace(pt[0],pt[1],pt[2]);
		}
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
	Point3f a = {0.0f ,1.0f ,0.0f};
	Point3f b = {-0.75f, -0.5f, -0.43f};
	Point3f c = {0.75f, -0.5f, -0.43f};
	Point3f d = {0.0f, -0.5f, 0.86f};

	// callsubdiv
	subdivideTriangle(a,b,c,step);
	subdivideTriangle(a,c,d,step);
	subdivideTriangle(a,d,b,step);
	subdivideTriangle(b,d,c,step);

	std::cout << "coordinate isze = " << coordinates.size() << std::endl;
}

void Mesh::subdivideTriangle(Point3f a, Point3f b, Point3f c, int n)
{
	if(n==0)
	{
		this->addFace(a,b,c);
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

void Mesh::createCube()
{
	// create a cube inscrit in a sphere of radius 1 centered in the origin
	coordinates.clear();
	coordinates.reserve(6*2*3*3);
	Point3f a = {-1,1, 1};
	Point3f b = {-1,1,-1};
	Point3f c = { 1,1,-1};
	Point3f d = { 1,1, 1};

	Point3f e = {-1,-1, 1};
	Point3f f = {-1,-1,-1};
	Point3f g = { 1,-1,-1};
	Point3f h = { 1,-1, 1};

	this->addSquareFace(a,b,c,d);
	this->addSquareFace(d,c,g,h);
	this->addSquareFace(h,g,f,e);
	this->addSquareFace(e,f,b,a);
	this->addSquareFace(e,a,d,h);
	this->addSquareFace(b,f,g,c);

	std::cout << "nb coord = " << coordinates.size() << std::endl;
}

