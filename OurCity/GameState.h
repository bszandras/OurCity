#pragma once


class GameState
{
private:
	int money;
	int baseTax = 500; // Legyen ez az alapad�
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
	int getBaseTax();
	int calculateTax();
	int getCurrentTax();
};