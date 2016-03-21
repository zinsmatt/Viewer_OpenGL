#include "face.h"
#include "vertex.h"

Face::Face(Vertex *a, Vertex *b, Vertex *c) : v1(a), v2(b), v3(c)
{
	Vector vector_1((double)(b->x-a->x),(double)(b->y-a->y),(double)(b->z-a->z),1.0);
	Vector vector_2((double)(c->x-a->x),(double)(c->y-a->y),(double)(c->z-a->z),1.0);

	/* the normale is normalized */
	normale = vector_1^vector_2;
	normale.normalize();
	normale *= -1;
}

Face::~Face()
{

}

