#include "mesh.h"
#include "viewer.h"
#include "face.h"
#include <cstring>
#include <iostream>
#include <set>
#include <GL/glew.h>

Mesh::Mesh() //: matrix(NULL)
{
	//matrix = new Matrixh;
}

Mesh::~Mesh()
{
	std::set<Vertex*> to_free;	//avoid to free a same vertex twice
	for(int iter = 0; iter<vertices.size(); ++iter)
		to_free.insert(vertices[iter]);
	std::cout << "size to free : " << to_free.size() << std::endl;
	for(std::set<Vertex*>::iterator it = to_free.begin(); it!=to_free.end(); ++it)
		delete *it;
	for(int iter = 0;iter<faces.size(); ++iter)
		delete faces[iter];
}

void Mesh::addFace(Vertex* a, Vertex *b, Vertex *c)
{	// add a triangle face
	faces.push_back(new Face(a,b,c));
}

void Mesh::addSquareFace(Vertex* a, Vertex* b, Vertex *c, Vertex *d, Vertex *center)
{	// add a square face decomposed in 4 triangles (a,b,c,d) in trigonometric order
	addFace(a,b,center);
	addFace(b,c,center);
	addFace(c,d,center);
	addFace(d,a,center);
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
	vertices.clear();
	faces.clear();
	std::cout << "createSphere(" << step << ")" << std::endl;
	//Point3f a = {0.0f ,1.0f ,0.0f};
	//Point3f b = {-0.75f, -0.5f, -0.43f};
	//Point3f c = { 0.75f, -0.5f, -0.43f};
	//Point3f d = {0.0f, -0.5f, 0.86f};

	Point3f a = {0.0f ,0.0f ,1.0f};
	Point3f b = {0.0f, 0.942809f, -0.333333f};
	Point3f c = { 0.816497f, -0.471405f, -0.333333f};
	Point3f d = {-0.816497f, -0.471405f, -0.333333f};
	float epsilon = 0.00001;

	// callsubdiv to fill vertices
	subdivideTriangle(a,c,b,step);
	subdivideTriangle(a,b,d,step);
	subdivideTriangle(a,d,c,step);
	subdivideTriangle(b,c,d,step);

	std::cout << vertices.size() << "vertices created" << std::endl;

	// merge coincident vertices
	int mergedVertices = 0;
	char *was_merged = new char[vertices.size()];
	memset(was_merged,0,vertices.size());
	for(int iter =0; iter < vertices.size(); iter++)
	{
		if(was_merged[iter] == 0)
		{
			for(int iter2 = 0; iter2 < vertices.size(); iter2++)
			{
				if(iter != iter2)
				{
					Vertex *vertex = vertices[iter];
					Vertex *comp = vertices[iter2];
					if(fabs(vertex->x-comp->x) < epsilon && fabs(vertex->y-comp->y) < epsilon
					   && fabs(vertex->z-comp->z) < epsilon)
					{
						delete comp;
						vertices[iter2] = vertex;
						was_merged[iter2] = 1;
						mergedVertices++;
					}
				}
			}
		}
	}
	std::cout << mergedVertices << " vertices were merged" << std::endl;
	std::cout << vertices.size()-mergedVertices << " vertices" << std::endl << std::endl;

	// create faces
	int iter = 0;
	while(iter < vertices.size())
	{
		addFace(vertices[iter],vertices[iter+1],vertices[iter+2]);
		iter += 3;
	}

	this->computeNormals();
}

void Mesh::subdivideTriangle(Point3f a, Point3f b, Point3f c, int n)
{
	if(n==0)
	{
		Vertex *v1 = newVertex(a[0],a[1],a[2]);
		Vertex *v2 = newVertex(b[0],b[1],b[2]);
		Vertex *v3 = newVertex(c[0],c[1],c[2]);
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

	vertices.clear();
	faces.clear();

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

	Vertex *adcb = newVertex(0,y,0);
	Vertex *hgcd = newVertex(x,0,0);
	Vertex *hefg = newVertex(0,-y,0);
	Vertex *eabf = newVertex(-x,0,0);
	Vertex *aehd = newVertex(0,0,z);
	Vertex *cgfb = newVertex(0,0,-z);

	this->addSquareFace(a,d,c,b,adcb);
	this->addSquareFace(h,g,c,d,hgcd);
	this->addSquareFace(h,e,f,g,hefg);
	this->addSquareFace(e,a,b,f,eabf);
	this->addSquareFace(a,e,h,d,aehd);
	this->addSquareFace(c,g,f,b,cgfb);

	this->computeNormals();
}

void Mesh::createCone(int steps, float height, float radius)
{
	/* create a cone with the base on the plan xOy */

	vertices.clear();
	faces.clear();

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

