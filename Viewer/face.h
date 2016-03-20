#ifndef FACE_H
#define FACE_H

struct Vertex;

class Face
{
	// represents only triangle faces
public:
	Face(Vertex *a,Vertex *b,Vertex *c);
	~Face();

	Vertex *v1;
	Vertex *v2;
	Vertex *v3;

	//Vertex* v1() const { return v1; }
	//Vertex* v2() const { return v2; }
	//Vertex* v3() const { return v3; }
};

#endif // FACE_H
