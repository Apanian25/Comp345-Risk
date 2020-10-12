#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include <iostream>




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

	vector<Territory*> terrToDef = Player2->toDefend();
	vector<Territory*> terrToAtk = Player1->toAttack();

	terrToDef.push_back(t1);
	terrToDef.push_back(t2);

	terrToAtk.push_back(t3);
	terrToAtk.push_back(t4);


	/*
		Looking at assignment operator
	*/
	Player* Player4 = Player2;

	/*
		Printing out players and some methods
	*/
	cout << *Player2;
	cout <<endl;
	cout << endl;

	Player2->issueOrder(or2);
	cout << endl;


	cout << *Player1;
	cout << endl;
	cout << endl;


	cout << *Player4;
	cout << endl;
	cout << endl;

	cout << *Player3 << endl;
	cout << endl;



	/*
		Printing out territories to attack
	*/
	cout << "\nTerritories that can attack" << endl;
	for (int i = 0; i < terrToAtk.size(); i++) {
		cout << *terrToAtk[i] << endl;
	}


	/*
		Printing out territories to defend
	*/
	cout << "\nTerritories that can defend" << endl;
	for (int i = 0; i < terrToDef.size(); i++) {
		cout << *terrToDef[i] << endl;
	}


	return 0;

}