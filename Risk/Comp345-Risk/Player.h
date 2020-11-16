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

	//vector<Territory*> territories;	
	//vector<Order*> orders;	
	//vector<Cards*> hand;	
	string player_name;
	int numOfArmies;

public:
	int id;
	vector<Territory*> territories;
	vector<Order*> orders;
	Hand* hand;
	bool hasConqueredTerritory;
	/*
	   Constructors and destructors
	*/
	Player(); //default constructor	
	Player(int id, string n); //constructor which creates a player with only it's name and id	
	Player(int id, string n, Hand* h, vector<Territory*> t, vector<Order*> o); //Constructtor which creates a player with a id, name, order, hand, and territory	
	Player(const Player& p); //Copy constructor	
	~Player(); //Destructor	
	/*
	   Methods for the player class
	*/
	int getNumOfArmies();
	void addTerritory(Territory* terr);   // Add a territory to the player, adding it to the territories list
	vector<Territory*> toAttack(); //Allows territories to attack	
	vector<Territory*> toDefend(); //Allows territories to defend	
	void giveArmies(int numOfArmies); //Gives armies to the player	
	Order* issueOrder(); //Gives order to the player and adds it to the other list	
	vector<Territory*> getTerritories();//the territories that the player owns	

	/*
	   Assignment and insertion operators
	*/
	Player& operator =(const Player& p);          //assignment operator	
	friend ostream& operator <<(ostream& strm, Player& player); //insertion operator	
};