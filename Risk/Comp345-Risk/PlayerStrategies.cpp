#include "PlayerStrategies.h"
#include "Player.h"
#include "Orders.h"

// *********************** HUMAN PLAYER ***********************
vector<Territory*> HumanPlayerStrategy::toAttack(Player* player)
{
	return vector<Territory*>();
}

vector<Territory*> HumanPlayerStrategy::toDefend(Player* player)
{
	return vector<Territory*>();
}

Order* HumanPlayerStrategy::issueOrder(Player* player)
{
	return nullptr;
}

// *********************** AGGRESSIVE PLAYER ***********************

vector<Territory*> AggressivePlayerStrategy::toAttack(Player* player)
{
	return vector<Territory*>();
}

vector<Territory*> AggressivePlayerStrategy::toDefend(Player* player)
{
	return vector<Territory*>();
}

Order* AggressivePlayerStrategy::issueOrder(Player* player)
{
	return nullptr;
}

// *********************** BENEVOLENT PLAYER ***********************

vector<Territory*> BenevolentPlayerStrategy::toAttack(Player* player)
{
	return vector<Territory*>();
}

vector<Territory*> BenevolentPlayerStrategy::toDefend(Player* player)
{
	return vector<Territory*>();
}

Order* BenevolentPlayerStrategy::issueOrder(Player* player)
{
	return nullptr;
}

// *********************** NEUTRAL PLAYER ***********************

vector<Territory*> NeutralPlayerStrategy::toAttack(Player* player)
{
	return player->toAttackUnSorted();
}

vector<Territory*> NeutralPlayerStrategy::toDefend(Player* player)
{
	return player->getTerritories();
}

Order* NeutralPlayerStrategy::issueOrder(Player* player)
{
	return nullptr;
}
