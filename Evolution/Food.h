#pragma once
#include <cstdlib>
#include "Coordinates.h"
class Food : public Coordinates{
public:
	//int x, y, z;
	int cal;
public:
	Food(){}
	Food(int Cal): cal(Cal){}
	Food(int X, int Y, int Z, int Cal) : Coordinates(X,Y,Z), cal(Cal) {}
	~Food() {}
};