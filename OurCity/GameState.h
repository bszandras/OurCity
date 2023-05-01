#pragma once


class GameState
{
private:
	int money;
	int baseTax = 500; // Legyen ez az alapad�
	short negativeYears = 0; // H�ny �ve negat�v a v�ros k�lts�gvet�se
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