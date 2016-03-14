#include "vector.h"

Vector::Vector(const double *v)
{
	for(int i=0;i<4;++i)
		values[i] = v[i];
}


Vector::Vector(double a, double b, double c, double d)
{
	values[0] = a;
	values[1] = b;
	values[2] = c;
	values[3] = d;
}

Vector& Vector::operator=(const Vector& v)
{
	for(int i=0;i<4;i++)
		values[i] = v[i];
}


Vector::~Vector()
{

}




std::ostream& operator<<(std::ostream& o, const Vector& v)
{
	o << v[0] << " ";
	o << v[1] << " ";
	o << v[2] << " ";
	o << v[3] << "\n";

	return o;
}
