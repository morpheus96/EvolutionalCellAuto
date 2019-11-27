#pragma once
#include <cstdlib>
#include <time.h>
#include "Food.h"

class Player {
private:
///vars
	int number;
	int energy=0;
	int age=0;
	int x, y;
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
	Player Multiply(const int &N) { 
		if ((rand() % 100) + 1 < basic_mutation_chance*energy) return Player(N, this->speed + rand()%2, this->sense + rand() % 2, this->size + rand() % 2);
		else return Player(N, this->speed, this->sense, this->size);
	}	
	void MoveRandom(){//map limits needs to be included
		if (rand() % 2) {
			if (rand()%2) x += speed;
			else x -= speed;
		}
		else {
			if (rand() % 2) y += speed;
			else y -= speed;
		}
	}
	void MoveToTarget(const Food& detected_food_list){
		
	}
};

int Player::basic_mutation_chance = 10;
int Player::basic_speed = 1;
int Player::basic_size = 1;
int Player::basic_sense = 1;