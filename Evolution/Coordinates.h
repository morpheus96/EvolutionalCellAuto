#pragma once
#include <math.h>

class Coordinates {
public:
	int x, y, z;
	bool status;
	//int rtype=0;
	Coordinates() {};
	~Coordinates() {};
	Coordinates(int X, int Y, int Z) : x(X), y(Y), z(Z) {};
	int distance(Coordinates* A){
		return abs(A->x - this->x)+ abs(A->y - this->y); // city metric
	}
	virtual int rType() = 0;
};