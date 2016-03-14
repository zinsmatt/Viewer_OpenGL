#include <iostream>
#include <iomanip>
#include <cmath>
#include "matrixh.h"
#include "vector.h"
#include <cstring>

Matrixh::Matrixh(const float *val)
{
	for(int i=0;i<16;i++)
	{
		if(val)
			this->rowMajorValues[i] = val[i];
		else
			this->rowMajorValues[i] = 0;
		if(val == NULL && (i == 0 || i == 5 || i == 10 || i == 15))
			this->rowMajorValues[i] = 1;
	}
}

Matrixh::~Matrixh()
{

}

const float* Matrixh::toColMajorMatrix()
{
	for(int i=0;i<4;++i)
	{
		for(int j=0;j<4;++j)
		{
			colMajorValues[j*4+i] = rowMajorValues[i*4+j];
		}
	}
	return colMajorValues;
}

void Matrixh::fromColMajorMatrix(const float *pt)
{
	memcpy(colMajorValues,pt,sizeof(float) * 16);
	int a=0;
	for(int i=0;i<4;++i)
	{
		for(int j=0;j<4;++j)
		{
			rowMajorValues[i+4*j] = colMajorValues[a++];
		}
	}
}

const float* Matrixh::toRowMajorMatrix() const
{
	return rowMajorValues;
}

void Matrixh::fromRowMajorMatrix(const float *pt)
{
	memcpy(rowMajorValues,pt,sizeof(float)*16);
}

void Matrixh::setIdentity()
{
	for(int i=0;i<16;i++)
	{
		this->rowMajorValues[i] = 0;
		if(i == 0 || i == 5 || i == 10 || i == 15)
			this->rowMajorValues[i] = 1;
	}
}

void Matrixh::setTranslation(float x, float y, float z)
{
	this->setIdentity();
	this->rowMajorValues[3] = x;
	this->rowMajorValues[7] = y;
	this->rowMajorValues[11] = z;
}

void Matrixh::setRotationX(float angle)
{	// angle in radians
	rowMajorValues[0] = 1;
	rowMajorValues[1] = 0;
	rowMajorValues[2] = 0;

	rowMajorValues[4] = 0;
	rowMajorValues[5] = cos(angle);
	rowMajorValues[6] = -sin(angle);

	rowMajorValues[8] = 0;
	rowMajorValues[9] = sin(angle);
	rowMajorValues[10] = cos(angle);

	rowMajorValues[3] = rowMajorValues[7] = rowMajorValues[11] = rowMajorValues[12] = rowMajorValues[13] = rowMajorValues[14] = 0;
	rowMajorValues[15] = 1;
}

void Matrixh::setRotationY(float angle)
{	// angle in radians
	rowMajorValues[0] = cos(angle);
	rowMajorValues[1] = 0;
	rowMajorValues[2] = sin(angle);

	rowMajorValues[4] = 0;
	rowMajorValues[5] = 1;
	rowMajorValues[6] = 0;

	rowMajorValues[8] = -sin(angle);
	rowMajorValues[9] = 0;
	rowMajorValues[10] = cos(angle);

	rowMajorValues[3] = rowMajorValues[7] = rowMajorValues[11] = rowMajorValues[12] = rowMajorValues[13] = rowMajorValues[14] = 0;
	rowMajorValues[15] = 1;
}

void Matrixh::setRotationZ(float angle)
{	// angle in radians
	rowMajorValues[0] = cos(angle);
	rowMajorValues[1] = -sin(angle);
	rowMajorValues[2] = 0;

	rowMajorValues[4] = sin(angle);
	rowMajorValues[5] = cos(angle);
	rowMajorValues[6] = 0;

	rowMajorValues[8] = 0;
	rowMajorValues[9] = 0;
	rowMajorValues[10] = 1;

	rowMajorValues[3] = rowMajorValues[7] = rowMajorValues[11] = rowMajorValues[12] = rowMajorValues[13] = rowMajorValues[14] = 0;
	rowMajorValues[15] = 1;
}

void Matrixh::setScale(float sx, float sy, float sz)
{
	this->setIdentity();
	rowMajorValues[0] = sx;
	rowMajorValues[5] = sy;
	rowMajorValues[10] = sz;
}

Vector Matrixh::operator*(const Vector& v)
{
	Vector res(0,0,0,0);
	for(int i=0;i<4;i++)
	{
		float temp = 0;
		for(int k=0;k<4;k++)
		{
			temp += rowMajorValues[4 * i + k] * v[k];
		}
		res.set(i,temp);
	}
	return res;
}

Matrixh Matrixh::operator *(const Matrixh& m)
{
	Matrixh res;
	for(int i=0;i<4;++i)
	{
		for(int j=0;j<4;++j)
		{
			float sum = 0;
			for(int k=0;k<4;++k)
			{
				sum += this->rowMajorValues[i*4+k] * m.rowMajorValues[4*k + j];
			}
			res.rowMajorValues[i*4+j] = sum;
		}
	}
	return res;
}




std::ostream& operator<<(std::ostream& o, const Matrixh& m)
{
	std::cout.precision(3);

	o << "\n";
	for(int i=0;i<4;++i)
	{
		for(int j=0;j<4;j++)
		{
			o << std::setw(10) << m.rowMajorValues[i*4+j] << " ";
		}
		o << "\n";
	}
	o << "\n";
	return o;
}
