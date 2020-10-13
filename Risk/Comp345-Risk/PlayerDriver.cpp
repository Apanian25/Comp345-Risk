#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include <iostream>


namespace PlayerDriver {

	int main() {

		/*
			Creating vectors and putting objects in that vector
		*/
		vector<Order*> order;
		vector<Territory*> terr;
		vector<Cards*> hand;

		Territory* t1 = new Territory("England", 14, 4);
		Territory* t2 = new Territory("Zimbabwe", 12, 3);
		Territory* t3 = new Territory();
		Territory* t4 = new Territory("Maritius", 13, 6);


		/*
			Adding some territories in the territory vector
		*/
		terr.push_back(t1);
		terr.push_back(t2);



		/*
			Adding cards in the card vector
		*/
		Cards* car1 = new Cards();
		Cards* car2 = new Cards();
		Cards* car3 = new Cards();


		hand.push_back(car1);
		hand.push_back(car2);
		hand.push_back(car3);

		/*
			Adding orders in the order vector
		*/

		Order* or1 = new Order();
		Order* or2 = new Order();


		order.push_back(or1);


		/*
			Here we created new players and push objects to some of the methods
		*/

		Player* Player1 = new Player();
		Player* Player2 = new Player("Jason", hand, terr, order);
		Player* Player3 = new Player("Mark");




		/*
			Looking at assignment operator
		*/
		Player* Player4 = Player2;

		/*
			Printing out players and some methods
		*/
		cout << *Player2 << endl;
		cout << endl;

		Player2->issueOrder(or2);
		cout << endl;


		cout << *Player1 << endl;
		cout << endl;


		cout << *Player4 << endl;
		cout << endl;

		cout << *Player3 << endl;
		cout << endl;


		/*
			Testing out the toAttack and toDefend method
		*/

		Player2->toAttack();
		Player2->toDefend();

		delete t1;
		t1 = NULL;
		delete t2;
		t2 = NULL;
		delete t3;
		t3 = NULL;
		delete t4;
		t4 = NULL;


		delete Player1;
		Player1 = NULL;
		delete Player2;
		Player2 = NULL;
		delete Player3;
		Player3 = NULL;
		

		/*
		* Player 4 pointed to the same memory location as Player 2, no need to delete it
		* delete Player4;
		*/
		Player4 = NULL;


		delete car1;
		car1 = NULL;
		delete car2;
		car2 = NULL;

		delete or1;
		or1 = NULL;
		delete or2;
		or2 = NULL;


		return 0;

	}
}

