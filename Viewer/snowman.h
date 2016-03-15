#ifndef SNOWMAN_H
#define SNOWMAN_H
#include "part.h"


class SnowMan : public Part
{
	friend class PartManager;
private:
	SnowMan();
	virtual ~SnowMan();
public:
	void moveHead(float azimut, float elevation);
};

#endif // SNOWMAN_H
