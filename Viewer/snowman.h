#ifndef SNOWMAN_H
#define SNOWMAN_H
#include "assembly.h"


class SnowMan : public Assembly
{
	friend class PartManager;
private:
	SnowMan(int id);
	virtual ~SnowMan();
public:
	void moveHead(float azimut, float elevation);
	virtual PART_TYPE getType() const { return SNOWMAN_ASSEMBLY; }
	virtual void showInfo() const;
};

#endif // SNOWMAN_H
