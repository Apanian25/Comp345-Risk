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
	this->strategy = nullptr;
}

Player::Player(int id, string n, PlayerStrategy* strategy)
{
	this->id = id;
	this->player_name = n;
	this->hand = new Hand();
	this->orders = vector<Order*>(0);
	this->territories = vector<Territory*>(0);
	this->hasConqueredTerritory = false;
	this->hasNegotiatedWithIds.push_back(-500);
	this->strategy = strategy;
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
	return this->strategy->toAttack();
}

vector<Territory*> Player::toAttackUnSorted() {
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

	return vecToAtk;
}

///<summary>
///Method which allows the player to defend themselves from other countries
///</summary>
vector<Territory*> Player::toDefend()
{
	this->strategy->toDefend();
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
	this->strategy->issueOrder();
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
	delete strategy;
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

void Player::setStrategy(PlayerStrategy* strategy)
{
	if (this->strategy != nullptr) 
		delete this->strategy;
	
	this->strategy = strategy;
}
