#include "abstractpart.h"
#include "matrixh.h"

AbstractPart::AbstractPart(int _id) : id(_id)
{
	matrix = new Matrixh;
}

AbstractPart::~AbstractPart()
{
	if(matrix) delete matrix;
}

void AbstractPart::setMatrix(const Matrixh& mat)
{
	if(matrix == NULL)
		matrix = new Matrixh;
	*matrix = mat;
}
