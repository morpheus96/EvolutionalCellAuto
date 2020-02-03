#pragma once


class Coordinates {
public:
	int x, y, z;
	Coordinates() {};
	~Coordinates() {};
	Coordinates(int X, int Y, int Z) : x(X), y(Y), z(Z) {};
};