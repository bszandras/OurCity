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
/// Megadja a j�t�kos egyenleg�t
/// </summary>
/// <returns>A j�t�kos egyenlege</returns>
int GameState::getMoney()
{
	return money;
}

/// <summary>
/// P�nt k�lt�se valamire
/// </summary>
/// <param name="amount">A k�ltend� �sszeg</param>
void GameState::spendMoney(int amount)
{
	money -= amount;
	//std::cout << money << std::endl;
}

/// <summary>
/// Bev�tel kezel�se
/// </summary>
/// <param name="amount">A bej�v� �sszeg</param>
void GameState::income(int amount)
{
	money += amount;
	//std::cout << money << std::endl;
}

/// <summary>
/// Megadja, hogy h�ny �ve negat�v a k�lts�gvet�s
/// </summary>
/// <returns></returns>
int GameState::getNegativeYears()
{
	return negativeYears;
}

/// <summary>
/// Hozz�ad egy �vet a negat�v k�lts�gvet�s� �vekhez
/// </summary>
void GameState::addNegativeYear()
{
	negativeYears++;
}

/// <summary>
/// Vissza�ll�tja a negat�v �vek sz�m�t
/// </summary>
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

/// <summary>
/// Tranzakci� hozz�ad�sa
/// </summary>
/// <param name="name">A tranzakci� neve</param>
/// <param name="amount">A tranzakci� �sszege</param>
void GameState::addTransaction(std::string name, int amount)
{
	transactions.push_back({ name, amount });
}

/// <summary>
/// Megadja a tranzakci�list�t
/// </summary>
/// <returns>Tranzakci�lista</returns>
std::vector<Transaction>* GameState::getTransactions()
{
	return &transactions;
}
