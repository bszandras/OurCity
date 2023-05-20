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
	//std::cout << money << std::endl;
}

void GameState::income(int amount)
{
	money += amount;
	//std::cout << money << std::endl;
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

/// <summary>
/// �j fenntart�si k�lts�g hozz�ad�sa.
/// </summary>
/// <param name="maintenance"> �j fenntart�si k�lts�g.</param>
void GameState::addToMaintenance(int maintenance)
{
	this->sumMaintenance += maintenance;
}

/// <summary>
/// Lebontott �p�let eset�n a fenntart�si k�lts�g kivon�sa.
/// </summary>
/// <param name="maintenance"> R�gi fenntart�si k�lts�g.</param>
void GameState::subFromMaintenance(int maintenance)
{
	this->sumMaintenance -= maintenance;
}

/// <summary>
/// Az �sszes�tett �ppeni fenntart�si k�lts�g.
/// </summary>
/// <returns></returns>
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
