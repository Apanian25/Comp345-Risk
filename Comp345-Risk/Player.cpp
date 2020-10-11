#include <iostream>
#include <stdio.h>
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "OrdersList.h"
#include <vector>
#include <list>
using namespace std;



// *********************************************************** PLAYER ***********************************************************


/// <summary>
/// Default constructor
/// </summary>

Player::Player() {

	this->player_name = "";
	this->hand = vector<Cards*>(0);
	this->orders = vector<Order*>(0);
	this->territories = vector<Territory*>(0);


}

/// <summary>
/// Parametrised constructor where we create a player with his own hand, territory, and order
/// </summary>

Player::Player(string n, vector<Cards*> h, vector<Territory*> t, vector<Order*> o)
{
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
	vector<Territory*> attackList;
	for (Territory* territory : territories) {
		for (Territory* attackable : territory->adjacentTerritoriesTo) {
			attackList.push_back(attackable);
		}
	}
	return attackList;

}
///<summary>
///Method which allows the player to defend themselves from adjacent countries adjacent countries
///</summary>
vector<Territory*> Player::toDefend()
{
	vector<Territory*> defendList;
	for (Territory* territory : territories) {
		for (Territory* defendable : territory->adjacentTerritoriesFrom) {
			defendList.push_back(defendable);
		}
	}
	return defendList;
}


///<summary>
///Method which will add an issued order to the orders list
/// </summary>
void Player::issueOrder(Order* order)
{
	this->orders.push_back(order);
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

	
	for (int i = 0; i < play.hand.size(); i++) {

		Cards* c = play.hand.at(i);
		this->hand.push_back(new Cards(*c));


		for (int i = 0; i < play.orders.size(); i++) {

			Order* order = play.orders.at(i);
			this->orders.push_back(new Order(*order));

		}

		for (int i = 0; play.territories.size(); i++) {

			Territory* terr = play.territories.at(i);
			this->territories.push_back(new Territory(*terr));

		}


	}

}
///<summary>
///Destructor for the player
/// </summary>
Player::~Player() {

	delete this;
}


///<summary>
///Method to print what territories the player owns, what his hands contains, and what are the orders he can issue
/// </summary>
ostream& operator<<(ostream& strm, Player& player)
{
	strm << "Player has " << player.territories.size() << " territories at his disposal.\n" << "He has "
		<< player.hand.size() << " number of cards.\n" << "And, he has " << player.orders.size() << " orders that he can use.";


	return strm;
}
