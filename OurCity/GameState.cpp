#include <iostream>

#include "GameState.h"
#include <math.h>

GameState::GameState()
{
	money = 100000;
	sumMaintenance = 0;
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

int GameState::getNegativeYears()
{
	return negativeYears;
}

void GameState::addNegativeYear()
{
	negativeYears++;
}

void GameState::resetNegativeYears()
{
	negativeYears = 0;
}

void GameState::addToMaintenance(int maintenance)
{
	this->sumMaintenance += maintenance;
}

void GameState::subFromMaintenance(int maintenance)
{
	this->sumMaintenance -= maintenance;
}

int GameState::getSumMaintenance()
{
	return this->sumMaintenance;
}

void GameState::addTransaction(std::string name, int amount)
{
	transactions.push_back({ name, amount });
}

std::vector<Transaction>* GameState::getTransactions()
{
	return &transactions;
}
