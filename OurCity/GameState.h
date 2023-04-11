#pragma once
class GameState
{
private:
	int money;
public:
	GameState();
	~GameState();
	int getMoney();
	void spendMoney(int amount);
	void income(int amount);
	bool hasEnough(int amount);
};