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
	int baseTax = 500; // Legyen ez az alapadó
	short negativeYears = 0; // Hány éve negatív a város költségvetése
	double taxRate = 1.0;
	int currentTax;
	int sumMaintenance;
	std::vector<Transaction> transactions;

public:
	GameState();
	~GameState();
	int getMoney();
	void spendMoney(int amount);
	void income(int amount);
	bool hasEnough(int amount);
	void setTaxRate(double rate);
	double getTaxRate();
	int getBaseTax();
	int calculateTax();
	int getCurrentTax();
	int getNegativeYears();
	void addNegativeYear();
	void resetNegativeYears();
	void addToMaintenance(int maintenance);
	void subFromMaintenance(int maintenance);
	int getSumMaintenance();

	void addTransaction(std::string name, int amount);
	std::vector<Transaction>* getTransactions();
};