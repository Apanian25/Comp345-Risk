#ifndef PLAYER_H
#define PLAYER_H

#pragma once
#include <stdio.h>
#include <iostream>
#include "Map.h"
#include "Cards.h"
#include "OrdersList.h"
#include <vector>
using namespace std;



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
	 Player(string n, vector<Cards*> h, vector<Territory*> t, vector<Order*> o); //Constructtor which creates a player with a name, order, hand, and territory
	 Player(const Player& p); //Copy constructor
	 ~Player(); //Destructor



	 /* 
	    Methods for the player class
	 */

	 vector<Territory*> toAttack(); //Allows territories to attack
	 vector<Territory*> toDefend(); //Allows territories to defend
	 void issueOrder(Order* order); //Gives order to the player
	 

	 /*
		Assignment and insertion operators
	 */

	 
	 Player& operator =(const Player& p);          //assignment operator
	 friend ostream& operator <<(ostream& strm, Player& player); //insertion operator

	 
	 




};

#endif