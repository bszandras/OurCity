#include <iostream>

#include "GameState.h"
#include <math.h>

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

void GameState::setTaxRate(double rate)
{
	this->taxRate = rate;
}

int GameState::calculateTax()
{
	int returnable = std::round(tax * taxRate);
	return returnable;
}
