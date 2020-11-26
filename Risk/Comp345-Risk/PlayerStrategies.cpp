#include "PlayerStrategies.h"

// *********************** HUMAN PLAYER ***********************
vector<Territory*> HumanPlayerStrategy::toAttack()
{
	return vector<Territory*>();
}

vector<Territory*> HumanPlayerStrategy::toDefend()
{
	return vector<Territory*>();
}

bool HumanPlayerStrategy::issueOrder()
{
	return false;
}

// *********************** AGGRESSIVE PLAYER ***********************

vector<Territory*> AggressivePlayerStrategy::toAttack()
{
	return vector<Territory*>();
}

vector<Territory*> AggressivePlayerStrategy::toDefend()
{
	return vector<Territory*>();
}

bool AggressivePlayerStrategy::issueOrder()
{
	return false;
}

// *********************** BENEVOLENT PLAYER ***********************

vector<Territory*> BenevolentPlayerStrategy::toAttack()
{
	return vector<Territory*>();
}

vector<Territory*> BenevolentPlayerStrategy::toDefend()
{
	return vector<Territory*>();
}

bool BenevolentPlayerStrategy::issueOrder()
{
	return false;
}

// *********************** NEUTRAL PLAYER ***********************

vector<Territory*> NeutralPlayerStrategy::toAttack()
{
	return vector<Territory*>();
}

vector<Territory*> NeutralPlayerStrategy::toDefend()
{
	return vector<Territory*>();
}

bool NeutralPlayerStrategy::issueOrder()
{
	return false;
}
