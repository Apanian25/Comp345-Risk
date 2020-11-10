#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Map.h"

using namespace std;

class Order {
public:
	bool isExecuted;
	Order();
	~Order();
	Order(const Order& a);
	virtual void execute(); //added this virtual method, so that the subclasses can override it
	virtual string getName() const;  // getName is used for the << operator to display the description of the order
	friend std::ostream& operator <<(std::ostream& stream, const Order& e);
	Order& operator = (const Order& a);
};

class Deploy : public Order {
public:
	int playerId;
	Territory* territoryPtr;

	int numOfArmies;
	string getName() const;
	bool validate();
	void execute();
	Deploy();  //no parameter  constructor  
	Deploy(int playerId, Territory* t, int numOfArmies);
	Deploy(const Deploy& d);      // copy constructor
	~Deploy();
	Deploy& operator=(const Deploy& d);  //assignment operator

};

class Advance : public Order {
public:
	int playerId;
	Territory* source;
	Territory* adjacent;
	int numOfArmies;
	int option;

	string getName() const;
	bool validate();
	void execute();
	Advance();
	Advance(int playerId, Territory* source, Territory* adjacent, int numOfArmies);
	Advance(const Advance& d);
	~Advance();
	Advance& operator = (const Advance& a);
};

class Bomb : public Order {
public:
	int playerId1;
	int playerId2;
	Territory* target;
	
	string getName() const;
	bool validate();
	void execute();
	Bomb();
	Bomb(int playerId1, int playerId2, Territory* target);
	Bomb(const Bomb& d);
	~Bomb();
	Bomb& operator = (const Bomb& a);
};

class Airlift : public Order {
public:
	int playerId; 
	Territory* source;
	Territory* target;
	int numOfArmies;
	int option;

	string getName() const;
	bool validate();
	void execute();
	Airlift();
	Airlift(int playerId, Territory* s, Territory* t, int numOfArmies);
	Airlift(const Airlift& d);
	~Airlift();
	Airlift& operator = (const Airlift& a);
};

class Blockade : public Order {
public:
	int playerId;
	Territory* target;

	string getName() const;
	bool validate();
	void execute();
	Blockade();
	Blockade(int playerId, Territory* t);
	Blockade(const Blockade& d);
	~Blockade();
	Blockade& operator = (const Blockade& a);
};

class Diplomacy : public Order {
public:
	//Player* source;
	//Player* target;

	string getName() const;
	bool validate();
	void execute();
	Diplomacy();
	Diplomacy(int playerId1, int playerId2);
	Diplomacy(const Diplomacy& d);
	~Diplomacy();
	Diplomacy& operator = (const Diplomacy& a);
};

class OrderList {
public:
	std::vector<Order*> list;   //list is a vector of pointer objects
	OrderList();                 //no parameter constructor
	OrderList(const OrderList& d);
	OrderList& operator =(const OrderList& e);
	~OrderList();                // destructor


	void remove(int ind);
	void move(int ind, int fin);

};

namespace OrdersDriver {
	int main();
}