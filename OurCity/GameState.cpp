#include <iostream>

#include "GameState.h"

GameState::GameState()
{
	money = 100000;
}

GameState::~GameState()
{
}

int GameState::getMoney()
{
	return money;
}

void GameState::spendMoney(int amount)
{
	money -= amount;
	std::cout << money << std::endl;
}

void GameState::income(int amount)
{
	money += amount;
	std::cout << money << std::endl;
}

bool GameState::hasEnough(int amount)
{
	return (money - amount) > 0;
}
