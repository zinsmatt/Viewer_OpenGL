#ifndef SNOWMAN_H
#define SNOWMAN_H
#include "part.h"


class SnowMan : public Part
{
	friend class PartManager;
protected:
	SnowMan();
	virtual ~SnowMan();
};

#endif // SNOWMAN_H
