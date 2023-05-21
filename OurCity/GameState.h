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
	short negativeYears = 0; // Hány éve negatív a város költségvetése
	int sumMaintenance;
	std::vector<Transaction> transactions;

public:
	GameState();
	~GameState();

	int getMoney();
	int getNegativeYears();
	void income(int amount);
	void spendMoney(int amount);
	void addNegativeYear();
	void resetNegativeYears();
	void addToMaintenance(int maintenance);
	void subFromMaintenance(int maintenance);
	int getSumMaintenance();

	void addTransaction(std::string name, int amount);
	std::vector<Transaction>* getTransactions();
};