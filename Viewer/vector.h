#ifndef VECTOR_H
#define VECTOR_H
#include <ostream>

class Vector
{
private:
	double values[4];
public:
	Vector() { values[0] = values[1] = values[2] = values[3] = 0.0; }
	Vector(const double* v);
	Vector(double a, double b, double c, double d);
	Vector& operator=(const Vector& v);
	~Vector();

	double operator[](int i) const { return values[i]; }
	void set(int i,double val) { if(i<4) values[i] = val; }
	void set(double a, double b, double c, double d) { values[0] = a; values[1] = b; values[2] = c; values[3] = d;}

	void normalize();
	Vector operator^(const Vector& v2);

};

std::ostream& operator<<(std::ostream& o, const Vector& v);

#endif // VECTOR_H
