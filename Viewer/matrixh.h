#ifndef MATRIXH_H
#define MATRIXH_H
#include <ostream>
#include <cstdlib>

class Vector;

class Matrixh
{
private:
	float rowMajorValues[16];		//this form is used
	float colMajorValues[16];		//only for input or output
public:

	friend std::ostream& operator<<(std::ostream& o, const Matrixh& m);

	Matrixh(const float* val = NULL);

	Matrixh(const Matrixh& m){
		for(int iter=0;iter<16;++iter)
			rowMajorValues[iter] = m.rowMajorValues[iter];
	}

	Matrixh& operator=(const Matrixh& m){
		for(int iter=0;iter<16;++iter)
			rowMajorValues[iter] = m.rowMajorValues[iter];
	}

	~Matrixh();

	void setIdentity();
	void setTranslation(float x, float y, float z);
	void setRotationX(float angle);
	void setRotationY(float angle);
	void setRotationZ(float angle);
	void setScale(float sx, float sy, float sz);

	const float* toColMajorMatrix();
	void fromColMajorMatrix(const float* pt);

	const float* toRowMajorMatrix() const;
	void fromRowMajorMatrix(const float *pt);


	Vector operator*(const Vector& v);
	Matrixh operator *(const Matrixh& m);
};

#endif // MATRIXH_H
