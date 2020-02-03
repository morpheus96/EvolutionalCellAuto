#pragma once
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include "Food.h"
#include "Player.h"
#include <string>

using namespace std;

class Map{

private:
	int size_x, size_y, size_z;
	int player_quantity;
	int food_per_level;
	
	int*** map_tab = new int**[size_x];
		
	vector<Coordinates*> map_map;

	std::list<Player> Players;
	Food *Foods = new Food[food_per_level];

public:
	Map(const int& X, const int& Y, const int& Z, const int& pq, const int& fpl) : size_x(X), size_y(Y), size_z(Z), player_quantity(pq), food_per_level(fpl)  {
		//Definition of map
		for (int i = 0; i < size_x; i++) map_tab[i] = new int*[size_y];
		for (int i = 0; i < size_x; i++) for (int j = 0; j < size_y; j++) map_tab[i][j] = new int[size_z];
		for (int i = 0; i < size_x; i++) for (int j = 0; j < size_y; j++) for (int k = 0; k < size_z; k++) map_tab[i][j][k] = 0;
		
	}
	~Map() {}
	void GC() {
		//for each(Player* pl in map_map);
		for (int i = 0; i < map_map.size(); ++i) {
			if (!(((Food* )map_map[i])->status)) {
				map_map.erase(map_map.begin() + i);
				cout << "plant eaten" << endl;
			}
			if (!(((Player*)map_map[i])->status)) {
				map_map.erase(map_map.begin() + i);
				cout << "player is dead" << endl;
			}
		}
	}
	void ProvideFood() {
		for (int k = 0; k<size_z; k++) {
			for (int a = 0; a < food_per_level; a++) map_map.push_back(new Food(rand()%4+1));
			for each (Food* pl in map_map)
			{
				if (pl->rType() == 1) {
					//cout << pl->rType();
					for (int i = 0; i < 1; i++) {//odpalone na krotko
						pl->x = rand() % size_x;
						pl->y = rand() % size_y;
						pl->z = k;
						pl->cal = rand() % 4 + 1;
						if (map_tab[pl->x][pl->y][k] != 0) {
							i = 0;
							break;
						}
						map_tab[pl->x][pl->y][pl->z] = 1;
					}
				}
			}
			//for (int i = 0; i < map_map.size(); i++) {
			//	if (map_map[i]->rType() == 1) {
			//		for (int j = 0; j < 1; j++) {//odpalone na krotko
			//			map_map[i]->x = rand() % size_x;
			//			map_map[i]->y = rand() % size_y;
			//			map_map[i]->z = k;
			//			if (map_tab[map_map[i]->x][map_map[i]->y][map_map[i]->z] != 0) {
			//				i = 0;
			//				break;
			//			}
			//			map_tab[map_map[i]->x][map_map[i]->y][map_map[i]->z] = 1;
			//		}
			//	}
			//}
		}
	}
	void ProvidePlayers() {
		for (int i = 0; i < player_quantity; i++) map_map.push_back(new Player());
		for each (Player* pl in map_map)
		{
			if (pl->rType()==2) {
				for (int i = 0; i < 1; i++) {//odpalone na krotko
					pl->x = rand() % size_x;
					pl->y = rand() % size_y;
					pl->z = 0;
					if (map_tab[pl->x][pl->y][0] != 0) {
						i = 0;
						break;
					}
					map_tab[pl->x][pl->y][0] = 2;
				}
			}
		}
	}
	void PlayGame() { //Wargame movie reference
		ProvidePlayers();
		for (int t = 0; t < 30; t++) {//turns
			ProvideFood();
			for (int ti = 0; ti < 10; ti++) {//turn iteration
				for each (Player* pl in map_map)
				{
					if (pl->rType() == 2) {
						pl->RefreshRange();
						while(pl->range>0){
							system("cls");
							DisplayMap("cos", t, ti);
							pl->RecognizeEnvironment(map_map, size_x, size_y, size_z);
							if (pl->seen) pl->MoveToTarget(size_x, size_y);
							else pl->MoveRandom(size_x, size_y, pl->speed);
							GC();
							RefreshMap();
							
							
						}
					}
					
				}
			}
			for each (Player* pl in map_map)
			{
				pl->GrowOld();
				if (pl->EnergyBilanse()) map_map.push_back(pl->Multiply(pl->x, pl->y, pl->z));
				else pl->Die();
			}
			GC();
		}
	}
	void DisplayMap(string name, int turn, int move) {
		cout << name << " : " << turn << " : " << move<< endl;
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
	void RefreshMap() {
		for (int i = 0; i < size_x; i++) for (int j = 0; j < size_y; j++) for (int k = 0; k < size_z; k++) map_tab[i][j][k] = 0;
		for each (Food* cor in map_map)
		{
			
			if (cor->rType() == 1) {
				map_tab[cor->x][cor->y][cor->z] = 1;
				//cout << cor->cal;
			}
		}
		for each (Player* cor in map_map)
		{
			if (typeid(cor).name()==typeid(Player*).name() && cor->rType() == 2) map_tab[cor->x][cor->y][cor->z] = 2;
			//cout << typeid(cor).name() << typeid(Player).name();
		}
		//for (int i = 0; i < size_x; i++) for (int j = 0; j < size_y; j++) for (int k = 0; k < size_z; k++) cout << map_tab[i][j][k]<<endl;
	}

};

