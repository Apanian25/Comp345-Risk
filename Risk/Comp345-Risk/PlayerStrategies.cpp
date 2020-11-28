#include "PlayerStrategies.h"
#include "Player.h"
#include "Orders.h"
#include <algorithm>

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
	vector<Territory*> vectToAtk = player->toAttackUnSorted();


	return vectToAtk;
}


vector<Territory*> BenevolentPlayerStrategy::toDefend(Player* player)
{
	 vector<Territory*> vecToDef = player->getTerritories();

	 std::sort(vecToDef.begin(), vecToDef.end(), [](Territory* t1, Territory* t2)
		 {
			 return t1->numberOfArmies < t2->numberOfArmies;
		 });

	 return vecToDef;
}

Order* BenevolentPlayerStrategy::issueOrder(Player* player)
{
	if (player->getNumOfArmies() > 0)
	{
		toDefend(player)[0];
		Deploy* deploy = new Deploy(player, toDefend(player)[0], player->getNumOfArmies());
		player->numOfArmies = 0;
		player->orders.push_back(deploy);
		return deploy;
	}
	else
	{

		if (player->hand->hand.size() > 0) 
		{
			std::cout << "this is for cards " << std :: endl;
		}

		else
		{
			vector<Territory*> toDef = toDefend(player);
			Territory* weakest = toDef[0];
			vector<Territory*> reinforcements = vector<Territory*>();

			for (Territory* canReinforceWith : weakest->adjacentTerritoriesFrom)
			{
				if (canReinforceWith->ownedBy = player->id && canReinforceWith->numberOfArmies > 0)
				{
					reinforcements.push_back(canReinforceWith);

				}
				
			}
			if (reinforcements.size() > 0)
			{
				std::sort(reinforcements.begin(), reinforcements.end(), [](Territory* t1, Territory* t2)
					{
						return t1->numberOfArmies > t2->numberOfArmies;
					});

				Advance* advance = new Advance(player, reinforcements[0], weakest, reinforcements[0]->numberOfArmies / 2);
				player->Notify("Added defending advance order");
				player->orders.push_back(advance);
				
			}
		}
		
	}
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
