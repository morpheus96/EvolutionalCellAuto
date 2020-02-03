#pragma once
#include <cstdlib>
#include "Coordinates.h"
class Food : public Coordinates{
public:
	//int x, y, z;
	int cal;
	bool status=true;
	int rtype = 1;
public:
	Food(){ status = true; }
	Food(int Cal): cal(Cal){ status = true; }
	Food(int X, int Y, int Z, int Cal) : Coordinates(X,Y,Z), cal(Cal) { status = true; }
	~Food() {}
	int rType() { return 1; }
};