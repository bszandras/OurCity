#pragma once
#include <vector>
#include <string>

struct Transaction
{
	std::string name;
	int amount;
};

class GameState
{
private:
	int money;
	short negativeYears = 0; // H�ny �ve negat�v a v�ros k�lts�gvet�se
	int sumMaintenance;
	std::vector<Transaction> transactions;

public:
	GameState();
	~GameState();
	int getMoney();
	void spendMoney(int amount);
	void income(int amount);
	bool hasEnough(int amount);
	int getNegativeYears();
	void addNegativeYear();
	void resetNegativeYears();
	void addToMaintenance(int maintenance);
	void subFromMaintenance(int maintenance);
	int getSumMaintenance();

	void addTransaction(std::string name, int amount);
	std::vector<Transaction>* getTransactions();
};