#include "point.h"
#include <cmath>
#include <iostream>

void normalise(Point3f pt)
{
	double n = 1.0f/std::sqrt(pt[0]*pt[0] + pt[1]*pt[1] + pt[2]*pt[2]);
	//std::cout << "n = " << n << std::endl;
	pt[0] *= n;
	pt[1] *= n;
	pt[2] *= n;
}
