#pragma once
#include "Map.h"
#include <vector>
#include "Player.h"

using namespace std;
class Player;

class PlayerStrategy {
public:
	virtual vector<Territory*> toAttack(Player* player) = 0;
	virtual vector<Territory*> toDefend(Player* player) = 0;
	virtual Order* issueOrder(Player* player) = 0;
};

class HumanPlayerStrategy : public PlayerStrategy {
public:
	vector<Territory*> toAttack(Player* player);
	vector<Territory*> toDefend(Player* player);
	Order* issueOrder(Player* player);
};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
	vector<Territory*> toAttack(Player* player);
	vector<Territory*> toDefend(Player* player);
	Order* issueOrder(Player* player);
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	vector<Territory*> toAttack(Player* player);
	vector<Territory*> toDefend(Player* player);
	Order* issueOrder(Player* player);
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
	vector<Territory*> toAttack(Player* player);
	vector<Territory*> toDefend(Player* player);
	Order* issueOrder(Player* player);
};