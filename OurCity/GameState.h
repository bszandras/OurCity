#pragma once
class GameState
{
private:
	int money;
	int baseTax = 500; // Legyen ez az alapadó
	double taxRate = 1.0;

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
};