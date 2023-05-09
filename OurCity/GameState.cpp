#include <iostream>

#include "GameState.h"
#include <math.h>

GameState::GameState()
{
	money = 100000;
	sumMaintenance = 0;
	currentTax = calculateTax();
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

// ENNEK A FUGGVENYNEK A MEGHIVASA UTAN KOZELEZO!!!! MEGHIVNI A RESIDENTMANAGER
// A RecalculateResidentTax() függvényét!
void GameState::setTaxRate(double rate)
{
	this->taxRate = rate;
	this->currentTax = calculateTax();
}

double GameState::getTaxRate()
{
	return taxRate;
}

int GameState::getBaseTax()
{
	return baseTax;
}

int GameState::calculateTax()
{
	int returnable = std::round(baseTax * taxRate);
	return returnable;
}

int GameState::getCurrentTax()
{
	return currentTax;
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
