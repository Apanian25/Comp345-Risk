#pragma once


#include <string>
#include <iostream>
#include <vector>
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

	string getName() const;
	bool validate();
	void execute();
	Deploy();                     //no parameter  constructor
	Deploy(const Deploy& d);      // copy constructor
	~Deploy();
	Deploy& operator=(const Deploy& d);  //assignment operator
};

class Advance : public Order {
public:
	string getName() const;
	bool validate();
	void execute();
	Advance();
	Advance(const Advance& d);
	~Advance();
	Advance& operator = (const Advance& a);
};
class Bomb : public Order {
public:
	string getName() const;
	bool validate();
	void execute();
	Bomb();
	Bomb(const Bomb& d);
	~Bomb();
	Bomb& operator = (const Bomb& a);
};
class Airlift : public Order {
public:
	string getName() const;
	bool validate();
	void execute();
	Airlift();
	Airlift(const Airlift& d);
	~Airlift();
	Airlift& operator = (const Airlift& a);
};
class Blockade : public Order {
public:
	string getName() const;
	bool validate();
	void execute();
	Blockade();
	Blockade(const Blockade& d);
	~Blockade();
	Blockade& operator = (const Blockade& a);
};
class Diplomacy : public Order {
public:
	string getName() const;
	bool validate();
	void execute();
	Diplomacy();
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