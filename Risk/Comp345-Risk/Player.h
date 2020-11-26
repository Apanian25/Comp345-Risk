#pragma once	
#include <stdio.h>	
#include <iostream>	
#include "Map.h"	
#include "Cards.h"	
#include "Orders.h"	
#include "GameObserver.h"
#include "PlayerStrategies.h"
#include <vector>	

using namespace std;
namespace PlayerDriver {
	int main();
}

class PlayerStrategy;

class Player : public Subject {
private:
	PlayerStrategy* strategy;
	string phase;
public:
	string player_name;
	int numOfArmies;
	int id;
	vector<Territory*> territories;
	vector<Order*> orders;
	vector<string> viewBuffer;
	Hand* hand;
	bool hasConqueredTerritory;
	vector <int> hasNegotiatedWithIds;
	


	/*
	   Constructors and destructors
	*/
	Player(); //default constructor
	Player(int id, string n); //constructor which creates a player with only it's name and id
	Player(int id, string n, PlayerStrategy* strategy); //constructor which creates a player with it's name, id, and custom strategy
	Player(int id, string n, Hand* h, vector<Territory*> t, vector<Order*> o); //Constructtor which creates a player with a id, name, order, hand, and territory
	Player(const Player& p); //Copy constructor
	~Player(); //Destructor

	/*
	   Methods for the player class
	*/
	int getNumOfArmies();
	void addTerritory(Territory* terr);
	vector<Territory*> toAttack(); //Allows territories to attack
	vector<Territory*> toAttackUnSorted();
	vector<Territory*> toDefend(); //Allows territories to defend
	void giveArmies(int numOfArmies); //Gives armies to the player
	Order* issueOrder(); //Gives order to the player and adds it to the other list
	vector<Territory*> getTerritories();//the territories that the player owns
	vector<string> getViewBuffer();
	void setPhase(string phase);
	string getPhase();
	void setStrategy(PlayerStrategy* strategy);

	/*
	   Assignment and insertion operators
	*/
	Player& operator =(const Player& p);          //assignment operator
	friend ostream& operator <<(ostream& strm, Player& player); //insertion operator
};