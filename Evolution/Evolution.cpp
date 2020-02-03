// Evolution.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "Player.h"
#include "Map.h"

int main()
{
	srand(time(0));
	Map* test = new Map(10, 10, 1, 1, 20);
	test->PlayGame();
	system("pause");
    return 0;
}

