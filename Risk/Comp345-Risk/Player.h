#ifndef PLAYER_H
#define PLAYER_H

#pragma once
#include <stdio.h>
#include <iostream>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include <vector>
using namespace std;

namespace PlayerDriver {
	int main();
}

class Player {

private:

	vector<Territory*> territories;
	vector<Order*> orders;
	vector<Cards*> hand;
	string player_name;


public:



	/*
	   Constructors and destructors
	*/

	Player(); //default constructor
	Player(string n); //constructor which creates a player with only it's name
	Player(string n, vector<Cards*> h, vector<Territory*> t, vector<Order*> o); //Constructtor which creates a player with a name, order, hand, and territory
	Player(const Player& p); //Copy constructor
	~Player(); //Destructor
	vector <Territory*> terrToAtk;
	vector<Territory*> terrToDef;




	/*
	   Methods for the player class
	*/

	vector<Territory*> toAttack(); //Allows territories to attack
	void toDefend(); //Allows territories to defend
	void issueOrder(Order* order); //Gives order to the player and adds it to the other list


	/*
	   Assignment and insertion operators
	*/


	Player& operator =(const Player& p);          //assignment operator
	friend ostream& operator <<(ostream& strm, Player& player); //insertion operator







};

#endif