#pragma once
#include <list>
#include "Player.h"

class Map{

private:
	int size_x, size_y, size_z;
	int player_quantity;
	int food_per_level;

	std::list<Player> Players;
	std::list<Food> Foods;

public:
	Map(const int& X, const int& Y, const int& Z, const int& pq, const int& fpl) : size_x(X), size_y(Y), size_z(Z), player_quantity(pq), food_per_level(fpl)  {
		for (int i = 0; i < player_quantity; i++) Players.push_back(Player(i));
	}
	~Map() {}

};

