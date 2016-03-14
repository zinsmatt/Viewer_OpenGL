#ifndef UTILITY_H
#define UTILITY_H
#include <iostream>

#define PI 3.14159265359
#define TO_DEGRES(x) x*180/PI
#define TO_RADIANS(x) x*PI/180

inline void print(float* t)
{
	for(int i=0;i<4;++i)
	{
		for(int j=0;j<4;j++)
		{
			std::cout << t[i+4*j] << " ";
		}
		std::cout << std::endl;
	}
}

#endif // UTILITY_H

