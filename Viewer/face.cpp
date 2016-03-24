#include "face.h"
#include "vertex.h"

Face::Face(Vertex *a, Vertex *b, Vertex *c) : v1(a), v2(b), v3(c)
{
	Vector vector_1((double)(b->x-a->x),(double)(b->y-a->y),(double)(b->z-a->z),1.0);
	Vector vector_2((double)(c->x-a->x),(double)(c->y-a->y),(double)(c->z-a->z),1.0);

	/* face normale*/
	normale = vector_1^vector_2;
	normale.normalize();

	a->addAdjacentFace(this);
	b->addAdjacentFace(this);
	c->addAdjacentFace(this);

	//normale *= -1;

	/* vertices normals */
	/*Vector na(a->nx,a->ny,a->nz,1.0);
	Vector nouv_na;
	nouv_na = na+normale;
	nouv_na.normalize();
	a->nx = nouv_na[0];
	a->ny = nouv_na[1];
	a->nz = nouv_na[2];

	Vector nb(b->nx,b->ny,b->nz,1.0);
	Vector nouv_nb;
	nouv_nb = nb+normale;
	nouv_nb.normalize();
	b->nx = nouv_nb[0];
	b->ny = nouv_nb[1];
	b->nz = nouv_nb[2];

	Vector nc(c->nx,c->ny,c->nz,1.0);
	Vector nouv_nc;
	nouv_nc = nc+normale;
	nouv_nc.normalize();
	c->nx = nouv_nc[0];
	c->ny = nouv_nc[1];
	c->nz = nouv_nc[2];*/
}

Face::~Face()
{

}

