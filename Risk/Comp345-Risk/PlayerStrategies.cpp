#include "PlayerStrategies.h"
#include "Player.h"
#include "Orders.h"
#include <algorithm>

using namespace std;

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
	vector<Territory*> vecToAtk = player->toAttackUnSorted();

	std::sort(vecToAtk.begin(), vecToAtk.end(), [](Territory* t1, Territory* t2) {
		//largest number of armies is first
		return t1->numberOfArmies > t2->numberOfArmies;
	});

	return vecToAtk;
}

vector<Territory*> AggressivePlayerStrategy::toDefend(Player* player)
{
	vector<Territory*> vecToDef = player->getTerritories();
	std::sort(vecToDef.begin(), vecToDef.end(), [](Territory* t1, Territory* t2) {
		//largest number of armies is first
		return t1->numberOfArmies > t2->numberOfArmies;
	});

	return vecToDef;
}

Order* AggressivePlayerStrategy::issueOrder(Player* player)
{
	if (player->getNumOfArmies() > 0) {
		//DEPLOY PHASE
		Deploy* dep = new Deploy(player, toDefend(player)[0], player->getNumOfArmies());
		player->orders.push_back(dep);
		player->numOfArmies = 0;
		return dep;
	}
	else {
		//DEPLOY PHASE COMPLETED 
		bool canPlayACard = false;
		if (player->hand->hand.size() > 0) {

			Order* order = player->hand->play(player);
			if (order != nullptr) {
				canPlayACard = true;
				player->orders.push_back(order);
				player->Notify("Added Deploy order");
			}
		}

		if(!canPlayACard) {
			vector<Territory*> toDef = toDefend(player);
			Territory* strongest = toDef[0];
			//REINFORCES STRONGEST
			for (Territory* canReinforceWith : toDef) {
				if (canReinforceWith == strongest)
					continue;
				if (std::count(strongest->adjacentTerritoriesFrom.begin(), strongest->adjacentTerritoriesFrom.end(), canReinforceWith) > 0) {
					canReinforceWith->commitedNumberOfArmies = canReinforceWith->numberOfArmies;
					Advance* reinf = new Advance(player, canReinforceWith, strongest, canReinforceWith->numberOfArmies);
					player->Notify("Added defending advance order");
					player->orders.push_back(reinf);
				}
			}
			//ATTACK EVERYTHING WE CAN
			for (Territory* territory : toAttack(player)) {
				for (Territory* canAttackWith : territory->adjacentTerritoriesFrom) {
					if (canAttackWith->ownedBy == player->id && canAttackWith->numberOfArmies > 0 && canAttackWith->commitedNumberOfArmies != canAttackWith->numberOfArmies) {
						canAttackWith->commitedNumberOfArmies = canAttackWith->numberOfArmies;
						Advance* adv = new Advance(player, canAttackWith, territory, canAttackWith->numberOfArmies);
						player->Notify("Added attacking advance order");
						player->orders.push_back(adv);
					}
				}
			}
		}
	}
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
