#pragma once
#include "Map.h"
#include <vector>

using namespace std;


class PlayerStrategy {
public:
	virtual vector<Territory*> toAttack() = 0;
	virtual vector<Territory*> toDefend() = 0;
	virtual bool issueOrder() = 0;
};

class HumanPlayerStrategy : public PlayerStrategy {
public:
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
	bool issueOrder();
};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
	bool issueOrder();
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
	bool issueOrder();
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
	bool issueOrder();
};