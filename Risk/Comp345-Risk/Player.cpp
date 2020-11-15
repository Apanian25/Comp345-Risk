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
	this->hasNegotiatedWithId = -500;

}

Player::Player(int id, string n)
{
	this->id = id;
	this->player_name = n;
	this->hand = new Hand();
	this->orders = vector<Order*>(0);
	this->territories = vector<Territory*>(0);
	this->hasConqueredTerritory = false;
	this->hasNegotiatedWithId = -500;


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
	this->hasNegotiatedWithId = -500;
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
	map<int, Territory*> terrToDef;

	//build a unique list of the territories that the player can attack
	for (Territory* territory : this->territories) {
		for (Territory* canDef : territory->adjacentTerritoriesFrom) {
			if (terrToDef.count(canDef->id) == 0) {
				//not already in the map
				terrToDef[canDef->id] = canDef;
			}
		}
	}

	vector<Territory*> vecToDef;
	for (pair<int, Territory*> territory : terrToDef) {
		vecToDef.push_back(territory.second);
	}

	std::sort(vecToDef.begin(), vecToDef.end(), [](Territory* t1, Territory* t2) {
		//better to defend territories with fewer armies.
		return t1->numberOfArmies < t2->numberOfArmies;
	});

	return vecToDef;
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
		//assume that the player owns at least 1 territory, if they don't have any territories, they are ejected from the gmae
		Deploy* dep = new Deploy(this, toDefend.at(0), armiesToDeploy); 
		this->orders.push_back(dep);
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

			//33% chance to advance(attack), advance(reinforce a territory) or stop issuing orders
			int luck = rand() % 3;
			bool attack = luck == 0;
			bool defend = luck == 1;


			if (attack) {
				bool isValidMove = false;
				int index = 0;
				vector<Territory*> defendable;
				vector<Territory*> listToAttack = this->toAttack();
				Territory* target = listToAttack.at(0);

				while (!isValidMove && index < listToAttack.size()) {
					target = listToAttack.at(index);
					for (Territory* territory : target->adjacentTerritoriesFrom) {
						if (territory->ownedBy == this->id) {
							defendable.push_back(territory);
						}
					}

					if (defendable.size() > 0)
						isValidMove = true;

					index++;
				}

				if (!isValidMove)
					return NULL; //cannot attack

				//sort in decreasing order of number of available armies
				std::sort(defendable.begin(), defendable.end(), [](Territory* t1, Territory* t2) {
					//better to attack a territory with more armies.
					return (t1->numberOfArmies - t1->commitedNumberOfArmies) > (t2->numberOfArmies - t2->commitedNumberOfArmies);
				});

				Territory* source = defendable.at(0);
				int availableArmies = source->numberOfArmies = source->commitedNumberOfArmies;
				if (availableArmies == 0)
					return NULL;

				int attackingArmies = 1 + (rand() % (source->numberOfArmies - source->commitedNumberOfArmies));
				if (target != NULL && availableArmies > target->numberOfArmies) {
					attackingArmies = target->numberOfArmies + (rand() % (availableArmies - target->numberOfArmies));
				}
				else {
					attackingArmies = 1 + (rand() % availableArmies);
				}

				source->commitedNumberOfArmies += attackingArmies;
				Advance* adv = new Advance(this, source, target, attackingArmies);
				return adv;
			}
			else if(defend) {
				if (toDefendWithArmiesLeft.size() < 2)
					return NULL;
				int src, targ;

				bool hasValidMove = false;
				for (int i = 0; i < toDefendWithArmiesLeft.size(); i++) {
					for (int j = i + 1; j < toDefendWithArmiesLeft.size(); j++) {
						if (toDefendWithArmiesLeft.at(i)->ownedBy == toDefendWithArmiesLeft.at(j)->ownedBy) {
							src = i;
							targ = j;
							hasValidMove = true;
							break;
						}
					}
					if (hasValidMove)
						break;
				}

				if (!hasValidMove)
					return NULL;

				Territory* source = toDefendWithArmiesLeft.at(src);
				Territory* target = toDefendWithArmiesLeft.at(targ);

				Advance* adv = new Advance(this, source, target, 1 + (rand() % (source->numberOfArmies - source->commitedNumberOfArmies)));
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
}


/// <summary>
/// Assignment operator; allows us to perform deep copy
/// </summary>
Player& Player::operator=(const Player& p)
{
	// copy orders
	this->orders = p.orders;
	this->hasNegotiatedWithId = p.hasNegotiatedWithId;
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
	this->hasNegotiatedWithId = play.hasNegotiatedWithId;

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
