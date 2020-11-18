#include <iostream>
#include <stdio.h>
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include "GameEngine.h"
#include <vector>
#include <algorithm>
#include <list>
#include <time.h> 
using namespace std;



// *********************************************************** PLAYER ***********************************************************




/// <summary>
/// Default constructor
/// </summary>

Player::Player() {

	this->id = -2;
	this->player_name = "";
	this->hand = new Hand();
	this->orders = vector<Order*>(0);
	this->territories = vector<Territory*>(0);
	this->hasConqueredTerritory = false;
	this->hasNegotiatedWithIds.push_back(-500);

}

Player::Player(int id, string n)
{
	this->id = id;
	this->player_name = n;
	this->hand = new Hand();
	this->orders = vector<Order*>(0);
	this->territories = vector<Territory*>(0);
	this->hasConqueredTerritory = false;
	this->hasNegotiatedWithIds.push_back(-500);


}

/// <summary>
/// Parametrised constructor where we create a player with his own hand, territory, and order
/// </summary>

Player::Player(int id, string n, Hand* h, vector<Territory*> t, vector<Order*> o)
{
	this->id = id;
	this->player_name = n;
	this->hand = h;
	this->territories = t;
	this->orders = o;
	this->hasConqueredTerritory = false;
	this->hasNegotiatedWithIds.push_back(-500);
}


///<summary>
///Method which allows the player to attack adjacent countries
/// </summary>
vector<Territory*> Player::toAttack()
{
	map<int, Territory*> terrToAtk;

	//build a unique list of the territories that the player can attack
	for (Territory* territory : this->territories) {
		for (Territory* canAttk : territory->adjacentTerritoriesTo) {
			if (terrToAtk.count(canAttk->id) == 0) {
				//not already in the map
				terrToAtk[canAttk->id] = canAttk;
			}
		}
	}

	vector<Territory*> vecToAtk;

	for (pair<int, Territory*> territory : terrToAtk) {
		vecToAtk.push_back(territory.second);
	}

	std::sort(vecToAtk.begin(), vecToAtk.end(), [](Territory* t1, Territory* t2) {
		//easier to conquer a territory with fewer armies.
		return t1->numberOfArmies < t2->numberOfArmies;
	});

	return vecToAtk;
}

///<summary>
///Method which allows the player to defend themselves from other countries
///</summary>
vector<Territory*>  Player::toDefend()
{
	std::sort(this->territories.begin(), this->territories.end(), [](Territory* t1, Territory* t2) {
		//better to defend territories with fewer armies.
		return t1->numberOfArmies < t2->numberOfArmies;
	});

	return this->territories;
}

int Player::getNumOfArmies() {
	return this->numOfArmies;
}

void Player::addTerritory(Territory* terr)
{
	this->territories.push_back(terr);
}

///<summary>
///Method which will add an issued order to the orders list
/// </summary>
Order* Player::issueOrder()
{
	// initialize random seed: this is done so that the rand object generates different random numbers on each run 
	srand(time(NULL));
	if (numOfArmies > 0) {
		//DEPLOY PHASE
		vector<Territory*> toDefend = this->toDefend();
		int armiesToDeploy =  1 + (rand() % this->numOfArmies); //from 1 - numOfArmies
		numOfArmies -= armiesToDeploy;

		Deploy* dep = new Deploy(this, toDefend.at(rand() % toDefend.size()), armiesToDeploy);
		this->orders.push_back(dep);
		this->Notify("Added Deploy order");
		return dep;
	}
	else {
		//DEPLOY PHASE DONE
		//Playing cards, if the player has any
		if (this->hand->hand.size() != 0) {
			Order* order = hand->play(this);
			orders.push_back(order);
			return order;
		}
		else {
			vector<Territory*> toDefend = this->toDefend();
			vector<Territory*> toDefendWithArmiesLeft;
			for (Territory* territory : toDefend) {
				if ((territory->numberOfArmies - territory->commitedNumberOfArmies) > 0)
					toDefendWithArmiesLeft.push_back(territory);
			}

			//we cannot create anymore deploy orders;
			if (toDefendWithArmiesLeft.size() == 0)
				return NULL;

			//chance to advance(attack), advance(reinforce a territory) or stop issuing orders
			int luck = rand() % 100;
			bool attack = luck < 98;
			bool defend = luck < 99;


			if (attack) {
				bool isValidMove = false;
				int index = 0;
				vector<Territory*> territoriesThatCanAttack;
				vector<Territory*> listToAttack = this->toAttack();
				Territory* target = listToAttack.at(0);

				while (!isValidMove && index < listToAttack.size()) {
					target = listToAttack.at(index);
					for (Territory* territory : target->adjacentTerritoriesFrom) {

						if (territory->ownedBy == this->id && territory->numberOfArmies - territory->commitedNumberOfArmies > 0) {
							bool foundDuplicateAttack = false;
							for (Order* order : this->orders) {
								Advance* advance = dynamic_cast<Advance*>(order);
								if (advance != NULL) {
									if (target->id == advance->target->id && territory->id == advance->source->id) {
										foundDuplicateAttack = true;
									}
								}
							}
							if(!foundDuplicateAttack)
								territoriesThatCanAttack.push_back(territory);
						}
					}

					if (territoriesThatCanAttack.size() > 0)
						isValidMove = true;

					++index;
				}

				if (!isValidMove)
					return NULL; //cannot attack

				//sort in decreasing order of number of available armies
				std::sort(territoriesThatCanAttack.begin(), territoriesThatCanAttack.end(), [](Territory* t1, Territory* t2) {
					//better to attack a territory with more armies.
					return (t1->numberOfArmies - t1->commitedNumberOfArmies) > (t2->numberOfArmies - t2->commitedNumberOfArmies);
				});

				Territory* source = territoriesThatCanAttack.at(0);
				int availableArmies = source->numberOfArmies - source->commitedNumberOfArmies;
				if (availableArmies == 0)
					return NULL;

				int attackingArmies = 0;
				if (target != NULL && availableArmies >= target->numberOfArmies) {
					if (availableArmies == target->numberOfArmies) {
						attackingArmies = availableArmies;
					}
					else {
						if (availableArmies - target->numberOfArmies - 1 == 0) {
							attackingArmies = availableArmies;
						}
						else {
							attackingArmies = target->numberOfArmies + 1 + (rand() % (availableArmies - target->numberOfArmies - 1));
						}
					}
				}
				else {
					int minArmiesToSend = 0.7 * availableArmies;
					attackingArmies = minArmiesToSend + (rand() % availableArmies-minArmiesToSend);
				}

				source->commitedNumberOfArmies += attackingArmies;
				Advance* adv = new Advance(this, source, target, attackingArmies);
				this->orders.push_back(adv);
				this->Notify("Added attacking advance order");
				return adv;
			}
			else if(defend) {
				if (toDefendWithArmiesLeft.size() < 2)
					return NULL;
				int src, targ;
				Territory* source = NULL, *target = NULL;
				bool hasValidMove = false;

				std::sort(toDefendWithArmiesLeft.begin(), toDefendWithArmiesLeft.end(), [](Territory* t1, Territory* t2) {
					return t1->numberOfArmies - t1->commitedNumberOfArmies < t2->numberOfArmies - t2->commitedNumberOfArmies;
				});

				for (Territory* territory : toDefendWithArmiesLeft) {
					for (Territory* adj : territory->adjacentTerritoriesTo) {
						if (territory->ownedBy == adj->ownedBy) {
							bool foundDuplicateDefend = false;
							for (Order* order : this->orders) {
								Advance* advance = dynamic_cast<Advance*>(order);
								if (advance != NULL) {
									if (adj->id == advance->target->id) {
										//Dont want to defend the same territory multiple times.
										foundDuplicateDefend = true;
									}
								}
							}
							if (!foundDuplicateDefend) {
								source = territory;
								target = adj;
								hasValidMove = true;
								break;
							}
						}
					}
					if (hasValidMove)
						break;
				}

				if (!hasValidMove)
					return NULL;

				int availableArmies = source->numberOfArmies - source->commitedNumberOfArmies;
				int numOfDefendingArmies =  1 + (rand() % (availableArmies));

				source->commitedNumberOfArmies += numOfDefendingArmies;
				Advance* adv = new Advance(this, source, target, numOfDefendingArmies);
				this->orders.push_back(adv);
				this->Notify("Added defending advance order");
				return adv;
			}
			else {
				return NULL; //NO MORE MOVES
			}
		}
	}

	return NULL;
}



vector<Territory*> Player::getTerritories() {
	return this->territories;
}

void Player::giveArmies(int numOfArmies) {
	this->numOfArmies += numOfArmies;
	Notify();
}


/// <summary>
/// Assignment operator; allows us to perform deep copy
/// </summary>
Player& Player::operator=(const Player& p)
{
	// copy orders
	this->orders = p.orders;
	this->hasNegotiatedWithIds = p.hasNegotiatedWithIds;
	this->hasConqueredTerritory = p.hasConqueredTerritory;

	// copy territories
	for (int i = 0; i < p.territories.size(); i++)
	{
		this->territories.push_back(p.territories.at(i));
	}

	//copies hand
	this->hand = p.hand; // assumes Hand assignment operator is correctly implemented

	return *this;

}

///<summary>
///Copy Constructor
///Creates a shallow copy
///</summary>
Player::Player(const Player& play) {
	this->numOfArmies = play.numOfArmies;
	this->id = play.id;
	this->hasConqueredTerritory = play.hasConqueredTerritory;
	this->hasNegotiatedWithIds = play.hasNegotiatedWithIds;

	this->hand = new Hand(*play.hand);

	for (int i = 0; i < play.orders.size(); i++) {
		Order* order = play.orders.at(i);
		this->orders.push_back(order);
	}

	for (int i = 0; play.territories.size(); i++) {
		Territory* terr = play.territories.at(i);
		this->territories.push_back(new Territory(*terr));
	}
}

///<summary>
///Destructor for the player
/// </summary>
Player::~Player() {


}


///<summary>
///Method to print what territories the player owns, what his hands contains, and what are the orders he can issue
/// </summary>
ostream& operator<<(ostream& strm, Player& player)
{
	strm <<"Player's name is " <<player.player_name << endl << player.player_name << " has " << player.territories.size() << " territories at their disposal." << endl << "He has "
		<< player.hand->hand.size() << " number of cards in his hand." << endl << "And, he has " << player.orders.size() << " orders that he can use.";

	return strm;
}

vector<string> Player::getViewBuffer()
{
	return viewBuffer;
}

void Player::setPhase(string phase) {
	this->phase = phase;
	Notify();
}

string Player::getPhase() {
	return this->phase;
}