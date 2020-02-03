#pragma once
#include <cstdlib>
#include <time.h>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include "Food.h"

class Player : public Coordinates {
public:
///vars
	int number;
	int energy=5;
	int age=0;
	bool status = true; //true - alive, false - dead
	//basic mutation parameters
	static int basic_mutation_chance;
	static int basic_speed;
	static int basic_size;
	static int basic_sense;
	//mutable parameters
	int speed;
	int size;
	int sense;
	int rtype = 2;
	int range;
	bool seen = false;
	std::pair<Food*, int>* target = new std::pair<Food*, int>{new Food(), 100000};
	std::vector<std::pair<Food*, int>*> detected_environ;
///getters
public:
	int GetSpeed() { return this->speed; }
	int GetSize() { return this->size; }
	int GetSense() { return this->sense; }
	bool GetStatus() { return this->status; }
///construtors
public:
	Player() : speed(basic_speed), sense(basic_sense), size(basic_size) { status = true; };
	Player(int X, int Y, int Z) : Coordinates(X, Y, Z), speed(basic_speed), sense(basic_sense), size(basic_size) { status = true; }
	Player(const int &Sp, const int &Se, const int &Si, int X, int Y, int Z) : Coordinates(X, Y, Z), speed(Sp), sense(Se), size(Si) { status = true; }
	Player(const Player &pl, int X, int Y, int Z) : Coordinates(X, Y, Z), speed(pl.speed), sense(pl.sense), size(pl.size) { status = true; }
	~Player() {}
///functions
public:
	int rType() { return 2; }
	void RefreshRange() { range = speed; }
	void Eat(const int& fcal) { energy+=fcal;  }
	void GrowOld() { age++; }
	void Die() { status = false; }
	void Starve() { if (!(energy > 0)) Die(); }
	bool EnergyBilanse() { return energy > speed*size * speed/2 + sense/2; }
	Player* Multiply(int X, int Y, int Z) {
		if ((rand() % 100) + 1 < basic_mutation_chance*energy) return new Player(this->speed + basic_speed*rand()%2, this->sense + basic_sense*rand() % 2, this->size + basic_size*rand() % 2, X, Y, Z);
		else return new Player(this->speed, this->sense, this->size, X, Y, Z);
	}	
	void MoveRandom(const int &size_x, const int &size_y, int Speed){
		if (rand() % 2) {
			if (rand()%2) x += Speed;
			else x -= Speed;
			if (x < 0) x = 0;
			if (x > size_x) x = size_x;
		}
		else {
			if (rand() % 2) y += Speed;
			else y -= Speed;
			if (y < 0) y = 0;
			if (y > size_y) y = size_y;
		}
	}
	void MoveToTarget(const int &size_x, const int &size_y){
		for (int i = 0; i < detected_environ.size(); i++) {
			if (detected_environ[i]->second < target->second) target = detected_environ[i];
		}
		if (target->second < range) {
			if (target->second < speed) {
				x = target->first->x;
				y = target->first->y;
				range -= target->second;
				Eat(target->first->cal);
				target->first->status = false;
			}
			else
			{
				for (int i = 0; i < speed; i++) {
					if (x < target->first->x) {
						x++;
						continue;
					}
					if (x > target->first->x) {
						x--;
						continue;
					}
					if (y < target->first->y) {
						x++;
						continue;
					}
					if (y > target->first->y) {
						y--;
						continue;
					}
					MoveRandom(size_x, size_y, speed - i);
					std::cout << "niemozliwe";
					break;
				}
			}
			
		}
		else
		{
			for (int i = 0; i < range; i++) {
				if (x < target->first->x) {
					x++;
					continue;
				}
				if (x > target->first->x) {
					x--;
					continue;
				}
				if (y < target->first->y) {
					x++;
					continue;
				}
				if (y > target->first->y) {
					y--;
					continue;
				}
				MoveRandom(size_x, size_y, range - i);
				std::cout << "niemozliwe";
				break;
			}
		}
	}
	void RecognizeEnvironment(std::vector<Coordinates*> map_map, int size_x, int size_y, int size_z) {
		detected_environ.clear();
		seen = false;
		for (int i = 0; i < size%8; i++) {
			if (i < size_z) {
				for each (Food* cor in map_map)
				{
					if (cor->z == i && cor->rType() == 1 && sense >= this->distance(cor)) {
						detected_environ.push_back(new std::pair<Food*, int>{ cor, this->distance(cor) });
						seen = true;
					}
				}
			}
		}
	}
};

int Player::basic_mutation_chance = 10;
int Player::basic_speed = 1;
int Player::basic_size = 1;
int Player::basic_sense = 1;