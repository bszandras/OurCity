#pragma once


class GameState
{
private:
	int money;
	int baseTax = 500; // Legyen ez az alapadó
	short negativeYears = 0; // Hány éve negatív a város költségvetése
	double taxRate = 1.0;
	int currentTax;

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
};