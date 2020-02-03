#pragma once
#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Food.h"
#include "Player.h"


class Map{

private:
	int size_x, size_y, size_z;
	int player_quantity;
	int food_per_level;
	
	int*** map_tab = new int**[size_x];
	

	std::list<Player> Players;
	Food *Foods = new Food[food_per_level];

public:
	Map(const int& X, const int& Y, const int& Z, const int& pq, const int& fpl) : size_x(X), size_y(Y), size_z(Z), player_quantity(pq), food_per_level(fpl)  {
		//Definition of map
		for (int i = 0; i < size_x; i++) map_tab[i] = new int*[size_y];
		for (int i = 0; i < size_x; i++) for (int j = 0; j < size_y; j++) map_tab[i][j] = new int[size_z];
		for (int i = 0; i < size_x; i++) for (int j = 0; j < size_y; j++) for (int k = 0; k < size_z; k++) map_tab[i][j][k] = 0;
		
		for (int i = 0; i < player_quantity; i++) Players.push_back(Player(i));
		for (int i = 0; i < food_per_level; i++) Foods[i].cal = rand() % 2 + 1;
		//for (int i = 0; i < food_per_level; i++) Foods[i] = Food(rand()%size_x, rand() % size_y, rand() % size_z, rand() % 4+1);
		for(int k=0; k<size_z; k++){
			for (int i = 0; i < food_per_level; i++) {
				for (int j = 0; j < 1; j++) {//odpalone na krotko
					Foods[i].x = rand() % size_x;
					Foods[i].y = rand() % size_y;
					Foods[i].z = k;
					if (map_tab[Foods[i].x][Foods[i].y][Foods[i].z] != 0) {
						i = 0;
						break;
					}
					map_tab[Foods[i].x][Foods[i].y][Foods[i].z] = 1;
				}
			}
		}
		for each (Player pl in Players)
		{
			for (int i = 0; i < 1; i++) {//odpalone na krotko
				pl.x = rand() % size_x;
				pl.y = rand() % size_y;
				if (map_tab[pl.x][pl.y][0] != 0) {
					i = 0;
					break;
				}
				map_tab[pl.x][pl.y][0] = 2;
			}
		}
	}
	void PlayGame() { //Wargame movie reference
		for (int t = 0; t < 20; t++) {
			//movement
		}
	}
	void DisplayMap(char name, int turn, int move) {
		
		for (int i = 0; i < size_y; i++) {
			for (int j = 0; j < size_z; j++) {
				for (int k = 0; k< size_x; k++) {
					if (map_tab[k][i][j] == 0) std::cout << " ";
					else std::cout << map_tab[k][i][j];
				}
				std::cout << " : ";
			}
			std::cout << std::endl;
		}
	}
	~Map() {}

};

