#ifndef UTILITY_H
#define UTILITY_H
#include <iostream>
#include <cmath>

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


inline float angleMajorValued(float angle)
{
	// return a value betweeb -180 and 180 degrees
	float mod = fmod(angle,360);
	if(mod>=0)
	{
		if(mod<=180)
			return mod;
		else
			return mod-360;
	}else
	{
		if(mod>=-180)
			return mod;
		else
			return mod+360;
	}
}

#endif // UTILITY_H

