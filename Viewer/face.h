#ifndef FACE_H
#define FACE_H
#include "vector.h"

struct Vertex;

class Face
{

private:
	Vector normale;

public:
	Face(Vertex *a,Vertex *b,Vertex *c);
	~Face();


	Vertex *v1;
	Vertex *v2;
	Vertex *v3;

	void getNormale(Vector& norm) const { norm = normale; }
};

#endif // FACE_H
