#pragma once


#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Order {
public:
	bool* ex = new bool();  //This boolean is used to determine if an order has been executed or not
	Order();
	virtual ~Order();
	Order(const Order& a);
	virtual void execute(); //added this virtual method, so that the subclasses can override it
	virtual string getName() const;  // getName is used for the << operator to display the description of the order
	friend std::ostream& operator <<(std::ostream& stream, const Order& e);
	Order& operator = (const Order& a);
};

class Deploy : public Order {
public:

	virtual string getName() const;
	bool validate();
	void execute();
	Deploy();                     //default constructor
	Deploy(const Deploy& d);      // copy constructor
	Deploy& operator=(const Deploy& d);  //assignment operator
};

class Advance : public Order {
public:
	virtual string getName() const;
	bool validate();
	void execute();
	Advance();
	Advance(const Advance& d);
	Advance& operator = (const Advance& a);
};
class Bomb : public Order {
public:
	virtual string getName() const;
	bool validate();
	void execute();
	Bomb();
	Bomb(const Bomb& d);
	Bomb& operator = (const Bomb& a);
};
class Airlift : public Order {
public:
	virtual string getName() const;
	bool validate();
	void execute();
	Airlift();
	Airlift(const Airlift& d);
	Airlift& operator = (const Airlift& a);
};
class Blockade : public Order {
public:
	virtual string getName() const;
	bool validate();
	void execute();
	Blockade();
	Blockade(const Blockade& d);
	Blockade& operator = (const Blockade& a);
};
class Diplomacy : public Order {
public:
	virtual string getName() const;
	bool validate();
	void execute();
	Diplomacy();
	Diplomacy(const Diplomacy& d);
	Diplomacy& operator = (const Diplomacy& a);
};

class OrderList {
public:
	std::vector<Order*> list;   //pointer to the list of Orders
	OrderList();                 //defaut constructor
	OrderList(const OrderList& d);
	OrderList& operator =(const OrderList& e);
	~OrderList();                // destructor


	void remove(int ind);
	void move(int ind, int final);

};
namespace OrdersDriver {
	int main();
}