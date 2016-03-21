#include "vector.h"
#include <cmath>

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

void Vector::normalize()
{
	double n = sqrt(values[0]*values[0] + values[1]*values[1] + values[2]*values[2]);
	double inverse = 1.0 / n;
	values[0] *= inverse;
	values[1] *= inverse;
	values[2] *= inverse;
}

Vector Vector::operator^(const Vector& v2)
{
	Vector resultat;
	double x,y,z;
	x = values[1]*v2.values[2] - values[2]*v2.values[1];
	y = values[2]*v2.values[0] - values[0]*v2.values[2];
	z = values[0]*v2.values[1] - values[1]*v2.values[0];
	resultat.set(x,y,z,1.0);
	return resultat;
}



std::ostream& operator<<(std::ostream& o, const Vector& v)
{
	o << v[0] << " ";
	o << v[1] << " ";
	o << v[2] << " ";
	o << v[3] << "\n";

	return o;
}
