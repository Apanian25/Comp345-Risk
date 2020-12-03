#include "PlayerStrategies.h"
#include "Player.h"
#include "Orders.h"
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>
#include "GameEngine.h"

using namespace std;

HumanPlayerStrategy::HumanPlayerStrategy(){}

// *********************** HUMAN PLAYER ***********************

/// <summary>
/// Returns the Territories that the Human player can attack
/// </summary>
/// <param name="player">The current player</param>
/// <returns></returns>
vector<Territory*> HumanPlayerStrategy::toAttack(Player* player)
{
	vector<Territory*> vecToAtk = player->toAttackUnSorted();

	std::sort(vecToAtk.begin(), vecToAtk.end(), [](Territory* t1, Territory* t2) {
		//largest number of armies is first
		return t1->numberOfArmies > t2->numberOfArmies;
		});

	for (int i = 0; i < vecToAtk.size(); i++)
	{
		cout << *vecToAtk[i] << endl;
	}

	return vecToAtk;
}

vector<Territory*> HumanPlayerStrategy::toDefend(Player* player)
{
	vector<Territory*> vecToDef = player->getTerritories();
	std::sort(vecToDef.begin(), vecToDef.end(), [](Territory* t1, Territory* t2) {
		//smallest number of armies is first
		return t1->numberOfArmies < t2->numberOfArmies;
		});
	
	return vecToDef;
}


Order* HumanPlayerStrategy::issueOrder(Player* player)
{
	int move = -1;
	while (move != 6) {
		int sourceId = -1;
		Territory* source = nullptr;
		int targetId = -1;
		Territory* target = nullptr;
		int numOfArmies = -1;
		//user choices here
		cout << "========================================" << endl;
		cout << "Player " << player->id <<"\'s turn, Please issue your orders: " << endl;
		cout << "0 - Display Territories to attack." << endl;
		cout << "1 - Display territories to defend." << endl;
		cout << "2 - Play a card." << endl;
		cout << "3 - Issue an advance order." << endl;
		cout << "4 - Issue a defend order." << endl;
		cout << "5 - Deploy armies." << endl;
		cout << "6 - Done Issuing Orders." << endl;
		cin >> move;
		switch (move)
		{
		case 0:
			toAttack(player);
			break;
		case 1:
			toDefend(player);
			break;
		case 2:
			player->hand->play(*player->hand, *player->orders, *deck);
			break;
		case 3:
		{
			cout << "Please choose a source territory(from territories you own): " << endl;
			vector<Territory*> playerOwnedTerritories = toDefend(player);
			for (int i = 0; i < playerOwnedTerritories.size(); i++)
			{
				if (playerOwnedTerritories[i]->numberOfArmies - playerOwnedTerritories[i]->commitedNumberOfArmies > 0) {
					cout << *playerOwnedTerritories[i] << endl;
				}
			}
			cout << "please enter the id of the source territory(enter -1 to exit): " << endl;
			cin >> sourceId;
			for (int i = 0; i < playerOwnedTerritories.size(); i++)
			{
				if (sourceId == playerOwnedTerritories[i]->id) {
					source = playerOwnedTerritories[i];
				}
			}
			if (source == nullptr) {
				break;
			}
			else {
				cout << "Please choose a target territory: " << endl;
				for (int i = 0; i < source->adjacentTerritoriesTo.size(); i++)
				{
					if (source->ownedBy != source->adjacentTerritoriesTo[i]->ownedBy) {
						cout << *source->adjacentTerritoriesTo[i] << endl;
					}
				}
				cout << "please enter the id of the target territory: " << endl;
				cin >> targetId;
				for (int i = 0; i < source->adjacentTerritoriesTo.size(); i++)
				{
					if (targetId == source->adjacentTerritoriesTo[i]->id) {
						target = source->adjacentTerritoriesTo[i];
					}
				}
				if (target == nullptr) {
					break;
				}
				else {
					cout << "Please choose the number of armies to move " << endl;
					while (numOfArmies > source->numberOfArmies - source->commitedNumberOfArmies || numOfArmies < 1) {
						cout << "Please enter a number between 1 and " << source->numberOfArmies - source->commitedNumberOfArmies << endl;
						cin >> numOfArmies;
					}
					player->orders->list.push_back(new Advance(player, source, target, numOfArmies));
					source->commitedNumberOfArmies += numOfArmies;
					player->Notify("Added attacking advance order.");
				}
			}
		}
			break;
		case 4: {

			cout << "Please choose a source territory(from territories you own): " << endl;
			vector<Territory*> playerOwnedTerritories = toDefend(player);
			for (int i = 0; i < playerOwnedTerritories.size(); i++)
			{
				if (playerOwnedTerritories[i]->numberOfArmies - playerOwnedTerritories[i]->commitedNumberOfArmies > 0) {
					cout << *playerOwnedTerritories[i] << endl;
				}
			}
			cout << "please enter the id of the source territory(enter -1 to exit): " << endl;
			cin >> sourceId;
			for (int i = 0; i < playerOwnedTerritories.size(); i++)
			{
				if (sourceId == playerOwnedTerritories[i]->id) {
					source = playerOwnedTerritories[i];
				}
			}
			if (source == nullptr) {
				break;
			}
			else {
				cout << "Please choose a target territory: " << endl;
				for (int i = 0; i < source->adjacentTerritoriesTo.size(); i++)
				{
					if (source->ownedBy == source->adjacentTerritoriesTo[i]->ownedBy) {
						cout << *source->adjacentTerritoriesTo[i] << endl;
					}
				}
				cout << "please enter the id of the target territory: " << endl;
				cin >> targetId;
				for (int i = 0; i < source->adjacentTerritoriesTo.size(); i++)
				{
					if (targetId == source->adjacentTerritoriesTo[i]->id) {
						target = source->adjacentTerritoriesTo[i];
					}
				}
				if (target == nullptr) {
					break;
				}
				else {
					cout << "Please choose the number of armies to move " << endl;
					while (numOfArmies > source->numberOfArmies - source->commitedNumberOfArmies || numOfArmies < 1) {
						cout << "Please enter a number between 1 and " << source->numberOfArmies - source->commitedNumberOfArmies << endl;
						cin >> numOfArmies;
					}
					player->orders->list.push_back(new Advance(player, source, target, numOfArmies));
					source->commitedNumberOfArmies += numOfArmies;
					player->Notify("Added defense advance order.");
				}
			}
		}
			break;
		case 5: {
			cout << "Please choose a source territory(from territories you own): " << endl;
			vector<Territory*> playerOwnedTerritories = toDefend(player);
			for (int i = 0; i < playerOwnedTerritories.size(); i++)
			{
				cout << *playerOwnedTerritories[i] << endl;
			}
			cout << "please enter the id of the source territory(enter -1 to exit): " << endl;
			cin >> sourceId;
			for (int i = 0; i < playerOwnedTerritories.size(); i++)
			{
				if (sourceId == playerOwnedTerritories[i]->id) {
					source = playerOwnedTerritories[i];
				}
			}
			if (source == nullptr) {
				break;
			}
			else {
				cout << "choose the number of armies you want to deploy: " << endl;
				cout << "please choose a number between 1 and " << player->numOfArmies << endl;
				cin >> numOfArmies;
				if (numOfArmies >= 1 && numOfArmies <= player->numOfArmies) {
					player->orders->list.push_back(new Deploy(player, source, numOfArmies));
					player->Notify("Added Deploy order");
				}
			}
		} break;
		default:
			break;
		}
	}

	return nullptr;
}

HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy& copy) {};

HumanPlayerStrategy& HumanPlayerStrategy::operator=(const HumanPlayerStrategy& x){return *this;}

HumanPlayerStrategy::~HumanPlayerStrategy(){}

// *********************** AGGRESSIVE PLAYER ***********************

AggressivePlayerStrategy::AggressivePlayerStrategy(){}

/// <summary>
/// Returns the Territories that the Aggressive player is allowed to attack,
/// The territores are sorted such that the territory with the largest number of armies is first.
/// </summary>
/// <param name="player">The current player</param>
/// <returns></returns>
vector<Territory*> AggressivePlayerStrategy::toAttack(Player* player)
{
	vector<Territory*> vecToAtk = player->toAttackUnSorted();

	std::sort(vecToAtk.begin(), vecToAtk.end(), [](Territory* t1, Territory* t2) {
		//largest number of armies is first
		return t1->numberOfArmies > t2->numberOfArmies;
	});

	return vecToAtk;
}

/// <summary>
/// Returns the Territories that the Aggressive player is allowed to defend,
/// The territores are sorted such that the territory with the largest number of armies is first.
/// </summary>
/// <param name="player">The current player</param>
/// <returns></returns>
vector<Territory*> AggressivePlayerStrategy::toDefend(Player* player)
{
	vector<Territory*> vecToDef = player->getTerritories();
	std::sort(vecToDef.begin(), vecToDef.end(), [](Territory* t1, Territory* t2) {
		//largest number of armies is first
		return t1->numberOfArmies > t2->numberOfArmies;
	});

	return vecToDef;
}

/// <summary>
/// This issues the orders that the Aggressive Player will decide to play.
/// The first type of orders that the player decides to play are Deploy orders.
/// Once the player cannot deploy any more armies on its territories then it decides attack
/// the strongest target(the one with the most armies) with all of its armies(from its territory with the most armies).
/// The Aggressive player also has access to play any cards that it wishes to play.
/// </summary>
/// <param name="player">The current player</param>
/// <returns></returns>
Order* AggressivePlayerStrategy::issueOrder(Player* player)
{
	if (player->getNumOfArmies() > 0) {
		//DEPLOY PHASE
		vector<Territory*> toDef = toDefend(player);
		Territory* strongest = nullptr;
		if (toDef[0]->numberOfArmies == 0) {
			//this is the first turn.
			for (Territory* def: toDef) {
				for (Territory* canAttack : def->adjacentTerritoriesTo) {
					if (canAttack->ownedBy != player->id) {
						strongest = canAttack;
					}
					if (strongest != nullptr)
						break;
				}
				if (strongest != nullptr)
					break;
			}
		}
		else {
			strongest = toDef[0];
		}

		Deploy* dep = new Deploy(player, toDefend(player)[0], player->getNumOfArmies());
		player->orders->list.push_back(dep);
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
				player->orders->list.push_back(order);
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
					player->orders->list.push_back(reinf);
				}
			}
			//ATTACK EVERYTHING WE CAN
			for (Territory* territory : toAttack(player)) {
				for (Territory* canAttackWith : territory->adjacentTerritoriesFrom) {
					if (canAttackWith->ownedBy == player->id && canAttackWith->numberOfArmies > 0 && canAttackWith->commitedNumberOfArmies != canAttackWith->numberOfArmies) {
						canAttackWith->commitedNumberOfArmies = canAttackWith->numberOfArmies;
						Advance* adv = new Advance(player, canAttackWith, territory, canAttackWith->numberOfArmies);
						player->Notify("Added attacking advance order");
						player->orders->list.push_back(adv);
					}
				}
			}
		}
	}
	return nullptr;
}

AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy& copy){}

AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy& x){return *this;}

AggressivePlayerStrategy::~AggressivePlayerStrategy(){}

// *********************** BENEVOLENT PLAYER ***********************

BenevolentPlayerStrategy::BenevolentPlayerStrategy(){}

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
		player->orders->list.push_back(deploy);
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
				if (canReinforceWith->ownedBy == player->id && canReinforceWith->numberOfArmies > 0)
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
				player->orders->list.push_back(advance);
				
			}
		}
		
	}
	return nullptr;
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& copy){}

BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy& x){return *this;}

BenevolentPlayerStrategy::~BenevolentPlayerStrategy(){}


// *********************** NEUTRAL PLAYER ***********************

NeutralPlayerStrategy::NeutralPlayerStrategy(){}

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

NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& copy){}

NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy& x){return *this;}

NeutralPlayerStrategy::~NeutralPlayerStrategy(){}

ostream& operator<<(ostream& out, const PlayerStrategy& x)
{
	out << "Player Strategy" << endl;
	return out;
}

ostream& operator<<(ostream& out, const HumanPlayerStrategy& x)
{
	out << "Human Player Strategy " << endl;
	return out;
}

ostream& operator<<(ostream& out, const AggressivePlayerStrategy& x)
{
	out << "Aggressive Player Strategy " << endl;
	return out;
}

ostream& operator<<(ostream& out, const BenevolentPlayerStrategy& x)
{
	out << "Benevolent Player Strategy " << endl;
	return out;
}

ostream& operator<<(ostream& out, const NeutralPlayerStrategy& x)
{
	out << "Neutral Player Strategy " << endl;
	return out;
}

PlayerStrategy::PlayerStrategy(){}

PlayerStrategy::~PlayerStrategy(){}

PlayerStrategy::PlayerStrategy(const PlayerStrategy& copy){}

PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& x){return *this;}
