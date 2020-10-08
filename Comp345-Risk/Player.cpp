#include <iostream>
#include <stdio.h>
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "OrdersList.h"
#include <vector>
#include <list>
using namespace std;


//Default constructor
Player::Player() {

	this->nb_Of_Players = ++count; //increases total number of players once they created 
	this->hand = vector<Cards*>;
	this->orders = vector<OrdersList*>;
	this->territories = vector<Territory*>;

}

//Method which allows the player to attack adjacent countries
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

//Method which allows the player to attack adjacent countries
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


//Method which will add an issued order to the orders list
void Player::issueOrder(OrdersList* order)
{
	this->orders.push_back(order);
}

//Copy Constructor
//Creates a shallow copy

Player::Player(const Player& play) {

	Player::Player();
	for (int i = 0; i < play.hand.size(); i++) {

		Cards* c = play.hand.at(i);
		this->hand.push_back(new Cards(*c));


		for (int i = 0; i < play.orders.size(); i++) {

			OrdersList* order = play.orders.at(i);
			this->orders.push_back(new OrdersList(*order));

		}

		for (int i = 0; play.territories.size(); i++) {

			Territory* terr = play.territories.at(i);
			this->territories.push_back(new Territory(*terr));

		}


	}

}

//Destructor for the player
Player::~Player() {

	delete this;
}



//Assignment operator 
//Performs a deep copy
Player& Player::operator=(const Player& player)
{

	//Copies order
	for (int i = 0; i < player.orders.size(); i++)
	{
		this->orders.push_back(player.orders.at(i));
	}
	//Copies hand 
	for (int i = 0; i < player.hand.size(); i++)
	{
		this->hand.push_back(player.hand.at(i));
	}
	//Copies territories
	for (int i = 0; i < player.territories.size(); i++)
	{
		this->territories.push_back(player.territories.at(i));
	}

	return *this;

}


//Method to print what territories the player owns, what his hands contains, and what are the orders he can issue
ostream& operator<<(ostream& strm, Player& player)
{
	cout << "Player has " << player.territories.size() << " territories at his disposal.\n" << "He has "
		<< player.hand.size() << " number of cards.\n" << "And, he has " << player.orders.size() << " orders that he can use.";


}
