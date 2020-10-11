#include "Player.h"
#include <iostream>


int main() {

	vector<Order*> order;
	vector<Territory*> terr;
	vector<Cards*> hand;

	Territory* t1 = new Territory("England", 14, 4);
	Territory* t2 = new Territory();

	terr.push_back(t1);
	terr.push_back(t2);

	Order* or1 = new Order();
	

	order.push_back(or1);

	


	string name = "jason";

	Player *Player1 = new Player();
	Player *Player2 = new Player(name, hand, terr, order);


	/*
		Looking at assignment operator
	*/
	Player* Player4 = Player1;




	





}