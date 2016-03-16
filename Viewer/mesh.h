#ifndef MESH_H
#define MESH_H
#include "point.h"
#include <vector>
#include <iterator>

class Matrixh;

class Mesh
{
private:
	std::vector<float> coordinates;
	void subdivideTriangle(Point3f a, Point3f b, Point3f c, int n);

public:

	Mesh();
	~Mesh();

	int getNbFaces() const { return (float)coordinates.size()/9; }

	void addFace(Point3f a,Point3f b,Point3f c);
	void addSquareFace(Point3f a, Point3f b, Point3f c, Point3f d);

	void draw(Matrixh &transf);
	void draw3(Matrixh *transf);

	void createSphere(int step, float radius = 1.0);
	void createCube(float x = 1.0, float y = 1.0, float z = 1.0);
	void createCone(int steps, float height = 1.0, float radius = 1.0);

	class CoordIterator
	{
		std::vector<float>::const_iterator iter;
	public:
		CoordIterator(const CoordIterator& it){
			this->iter = it.iter;
		}
		CoordIterator(std::vector<float>::const_iterator it){
			this->iter = it;
		}

		float operator*(){
			return *(iter);
		}

		CoordIterator& operator++(){
			++iter;
			return *this;
		}
		CoordIterator operator++(int){
			CoordIterator temp(*this);
			iter++;
			return temp;
		}
		bool operator!=(const CoordIterator& it){
			return this->iter != it.iter;
		}
	};

	CoordIterator begin(){
		return CoordIterator(coordinates.begin());
	}
	CoordIterator end(){
		return CoordIterator(coordinates.end());
	}
};

#endif // MESH_H
