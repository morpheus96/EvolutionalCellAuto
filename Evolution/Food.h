#pragma once

class Food{
private:
	int x, y, z;
	int cal;
public:
	Food(int X, int Y, int Z, int Cal) : x(X), y(Y), z(Z), cal(Cal) {}
	~Food() {}
};