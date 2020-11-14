#include <iostream>
#include <stdio.h>
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
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

	this->player_name = "";
	this->hand = new Hand();
	this->orders = vector<Order*>(0);
	this->territories = vector<Territory*>(0);


}

Player::Player(int id, string n)
{
	this->id = id;
	this->player_name = n;
	this->hand = new Hand();
	this->orders = vector<Order*>(0);
	this->territories = vector<Territory*>(0);


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
		//Deploy Phase
		vector<Territory*> toDefend = this->toDefend ();
		int index = rand() % toDefend.size(); // from 0 - (size - 1)
		int armiesToDeploy =  1 + (rand() % this->numOfArmies); //from 1 - numOfArmies
		//should call Deploy here
		toDefend.at(index)->addArmies(1);
		numOfArmies -= armiesToDeploy;
		Deploy* dep = new Deploy();
		return dep;
	}
	else {
		//Deploy phase done
		if (this->hand->hand.size() != 0) {
			Cards* card = this->hand->hand.at(0);
			Order* order;

			switch (card->type) {
			case 0:
				order = new Bomb();
				break;
			case 2:
				order = new Blockade();
				break;
			case 3:
				order = new Airlift();
				break;
			case 4:
				order = new Diplomacy();
				break;
			}


			orders.push_back(order);
			return order;
		}
		else {
			//check if there are any armies on our territories, if there are we can have a 50/50 to choose to attack
			bool attack = (rand() % 2) == 0; // from 0 - 1
			if (attack) {
				//choose a territory and number of armies to send.
				Advance* adv = new Advance();
				return adv;
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
