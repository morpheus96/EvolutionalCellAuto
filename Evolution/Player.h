#pragma once
#include <cstdlib>
#include <time.h>
#include <vector>
#include <algorithm>
#include "Food.h"

class Player : public Coordinates {
private:
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

	std::pair<Coordinates, int> detected_environ;
public:
	int x, y;
///getters
public:
	int GetSpeed() { return this->speed; }
	int GetSize() { return this->size; }
	int GetSense() { return this->sense; }
	bool GetStatus() { return this->status; }
///construtors
public:
	Player(const int &N) : number(N), speed(basic_speed), sense(basic_sense), size(basic_size) {}
	Player(const int &N, const int &Sp, const int &Se, const int &Si) : number(N), speed(Sp), sense(Se), size(Si) {}
	Player(const int &N, const Player &pl) : number(N), speed(pl.speed), sense(pl.sense), size(pl.size) { }
	~Player() {}
///functions
public:
	void Eat(const int& fcal) { energy+=fcal; }
	void GrowOld() { age++; }
	void Die() { status = false; }
	void Starve() { if (!(energy > 0)) Die(); }
	bool EnergyBilanse() { return energy > speed*size * 10; }
	Player Multiply(const int &N) { 
		if ((rand() % 100) + 1 < basic_mutation_chance*energy) return Player(N, this->speed + rand()%2, this->sense + rand() % 2, this->size + rand() % 2);
		else return Player(N, this->speed, this->sense, this->size);
	}	
	void MoveRandom(const int &size_x, const int &size_y){//map limits needs to be included
		if (rand() % 2) {
			if (rand()%2) x += speed;
			else x -= speed;
			if (x < 0) x = 0;
			if (x > size_x) x = size_x;
		}
		else {
			if (rand() % 2) y += speed;
			else y -= speed;
			if (y < 0) y = 0;
			if (y > size_y) y = size_y;
		}
	}
	void MoveToTarget(const Food& detected_food_list){
		
	}
	void RecognizeEnvironment(const int*** map, int size_x, int size_y, int size_z) {
		for (int i = x - sense; i < x + sense; i++) {
			for (int j = y - sense; j < y + sense; j++) {
				for (int k = 0; k < size % 8; k++) {
					if (x >= 0 && x < size_x && y >= 0 && y < size_y && k >= 0 && k < size_z) {

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