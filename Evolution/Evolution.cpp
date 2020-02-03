// Evolution.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "Player.h"
#include "Map.h"

int main()
{
	srand(time(0));
	Map* test = new Map(20, 20, 2, 10, 10);
	test->DisplayMap();
	system("pause");
    return 0;
}

