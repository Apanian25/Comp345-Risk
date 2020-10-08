#pragma once

#include <stdio.h>
#include <iostream>
#include "Map.h"
#include "Cards.h"
#include "OrdersList.h"
#include <list>
#include <vector>
using namespace std;

namespace Player {
	int main();


}

class Player {

private:

	int count{0};
	int nb_Of_Players;
	vector<Territory*> territories; 
	vector<OrdersList*> orders;
	vector<Cards*> hand;
	string player_name;


 public:

	 Player(); //default constructor
	 Player(const Player& p); //Copy constructor
	 vector<Territory*> toAttack();
	 vector<Territory*> toDefend();
	 void issueOrder(OrdersList* order);
	 
	 Player& operator =(const Player& player);          //assignment operator
	 friend ostream& operator <<(ostream& strm, Player& player); //insertion operator

	 
	 




};