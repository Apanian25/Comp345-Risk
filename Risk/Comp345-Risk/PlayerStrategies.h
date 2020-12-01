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
	PlayerStrategy();
	~PlayerStrategy();
private:
	PlayerStrategy(const PlayerStrategy& copy);
	PlayerStrategy& operator= (const PlayerStrategy& x);
	friend ostream& operator<< (ostream& out, const PlayerStrategy& x);
};

class HumanPlayerStrategy : public PlayerStrategy {
public:
	HumanPlayerStrategy();
	vector<Territory*> toAttack(Player* player);
	vector<Territory*> toDefend(Player* player);
	Order* issueOrder(Player* player);
	HumanPlayerStrategy(const HumanPlayerStrategy& copy);
	HumanPlayerStrategy& operator= (const HumanPlayerStrategy& x);
	friend ostream& operator<< (ostream& out, const HumanPlayerStrategy& x);
	~HumanPlayerStrategy();
};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
	AggressivePlayerStrategy();
	vector<Territory*> toAttack(Player* player);
	vector<Territory*> toDefend(Player* player);
	Order* issueOrder(Player* player);
	AggressivePlayerStrategy(const AggressivePlayerStrategy& copy);
	AggressivePlayerStrategy& operator= (const AggressivePlayerStrategy& x);
	friend ostream& operator<< (ostream& out, const AggressivePlayerStrategy& x);
	~AggressivePlayerStrategy();
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	BenevolentPlayerStrategy();
	vector<Territory*> toAttack(Player* player);
	vector<Territory*> toDefend(Player* player);
	Order* issueOrder(Player* player);
	BenevolentPlayerStrategy(const BenevolentPlayerStrategy& copy);
	BenevolentPlayerStrategy& operator= (const BenevolentPlayerStrategy& x);
	friend ostream& operator<< (ostream& out, const BenevolentPlayerStrategy& x);
	~BenevolentPlayerStrategy();
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
	NeutralPlayerStrategy();
	vector<Territory*> toAttack(Player* player);
	vector<Territory*> toDefend(Player* player);
	Order* issueOrder(Player* player);
	NeutralPlayerStrategy(const NeutralPlayerStrategy& copy);
	NeutralPlayerStrategy& operator= (const NeutralPlayerStrategy& x);
	friend ostream& operator<< (ostream& out, const NeutralPlayerStrategy& x);
	~NeutralPlayerStrategy();
};