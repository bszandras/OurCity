#include <iostream>

#include "GameState.h"
#include <math.h>

/// <summary>
/// GameState konstruktor
/// </summary>
GameState::GameState()
{
	money = 100000;
	sumMaintenance = 0;
}

GameState::~GameState()
{
}

/// <summary>
/// Megadja a játékos egyenlegét
/// </summary>
/// <returns>A játékos egyenlege</returns>
int GameState::getMoney()
{
	return money;
}

/// <summary>
/// Pént költése valamire
/// </summary>
/// <param name="amount">A költendõ összeg</param>
void GameState::spendMoney(int amount)
{
	money -= amount;
	//std::cout << money << std::endl;
}

/// <summary>
/// Bevétel kezelése
/// </summary>
/// <param name="amount">A bejövõ összeg</param>
void GameState::income(int amount)
{
	money += amount;
	//std::cout << money << std::endl;
}

/// <summary>
/// Megadja, hogy hány éve negatív a költségvetés
/// </summary>
/// <returns></returns>
int GameState::getNegativeYears()
{
	return negativeYears;
}

/// <summary>
/// Hozzáad egy évet a negatív költségvetésû évekhez
/// </summary>
void GameState::addNegativeYear()
{
	negativeYears++;
}

/// <summary>
/// Visszaállítja a negatív évek számát
/// </summary>
void GameState::resetNegativeYears()
{
	negativeYears = 0;
}

/// <summary>
/// Új fenntartási költség hozzáadása.
/// </summary>
/// <param name="maintenance"> Új fenntartási költség.</param>
void GameState::addToMaintenance(int maintenance)
{
	this->sumMaintenance += maintenance;
}

/// <summary>
/// Lebontott épület esetén a fenntartási költség kivonása.
/// </summary>
/// <param name="maintenance"> Régi fenntartási költség.</param>
void GameState::subFromMaintenance(int maintenance)
{
	this->sumMaintenance -= maintenance;
}

/// <summary>
/// Az összesített éppeni fenntartási költség.
/// </summary>
/// <returns></returns>
int GameState::getSumMaintenance()
{
	return this->sumMaintenance;
}

/// <summary>
/// Tranzakció hozzáadása
/// </summary>
/// <param name="name">A tranzakció neve</param>
/// <param name="amount">A tranzakció összege</param>
void GameState::addTransaction(std::string name, int amount)
{
	transactions.push_back({ name, amount });
}

/// <summary>
/// Megadja a tranzakciólistát
/// </summary>
/// <returns>Tranzakciólista</returns>
std::vector<Transaction>* GameState::getTransactions()
{
	return &transactions;
}
