#include<iostream>
#include <string>
#include "Orders.h"

using namespace std;

Order::Order() {
	*ex = false; //this is the boolean member that checks if an order has been executed
};

Order::Order(const Order& a) {
	this->ex = new bool(*(a.ex));
}
Order::~Order() {}
void Order::execute() {}

string Order::getName() const {
	return "This is an unspecified order ";
}

std::ostream& operator<<(std::ostream& stream, const  Order& e)
{
	return stream << e.getName();
}
Order& Order::operator=(const Order& a) {
	this->ex = new bool(*(a.ex));
	return *this;
}
string Deploy::getName() const {
	if (*ex) {									//returns a different string depending on ex
		return "The Deploy order has been executed, armies are on the territory";
	}
	else {
		return "This is a Deploy order";
	}
}
bool Deploy::validate() {
	if (1)
		return true;       // since there are no way to validate in the game yet, just return true
}
void Deploy::execute() {
	*ex = validate();        // if an order performs execute, ex turns to true
};
Deploy::Deploy() {}

Deploy::Deploy(const Deploy& d) : Order(d) {}

Deploy& Deploy::operator=(const Deploy& d) {
	Order::operator=(d);
	return *this;
}

string Bomb::getName() const {
	if (*ex) {
		return "The Bomb order has been executed, half of enemy armies are eliminated";
	}
	else {
		return "This is a Bomb order";
	}
}
bool Bomb::validate() {
	if (1)
		return true;
};
void Bomb::execute() {
	*ex = validate();
};
Bomb::Bomb() {};

Bomb::Bomb(const Bomb& d) : Order(d) {}

Bomb& Bomb::operator=(const Bomb& d) {
	Order::operator=(d);
	return *this;
}

string Airlift::getName() const {
	if (*ex) {
		return "The Airlift order has been executed, armies are on the territory";
	}
	else {
		return "This is a Airlift order";
	}
}
bool Airlift::validate() {
	if (1)
		return true;
};
void Airlift::execute() {
	*ex = validate();
}
Airlift::Airlift() {};

Airlift::Airlift(const Airlift& d) : Order(d) {}

Airlift& Airlift::operator=(const Airlift& d) {
	Order::operator=(d);
	return *this;
}

string Advance::getName() const {
	if (*ex) {
		return "The Advance order has been executed, armies are on the territory";
	}
	else {
		return "This is a Advance order";
	}
}
bool Advance::validate() {
	if (1)
		return true;
};
void Advance::execute() {
	*ex = validate();
};
Advance::Advance() {};

Advance::Advance(const Advance& d) : Order(d) {}

Advance& Advance::operator=(const Advance& d) {
	Order::operator=(d);
	return *this;
}

string Blockade::getName() const {
	if (*ex) {
		return "The Blockade order has been executed, the number of armies has tripled and the territory is neutral";
	}
	else {
		return "This is a Blockade order";
	}
}
bool Blockade::validate() {
	if (1)
		return true;
};
void Blockade::execute() {
	*ex = validate();
};
Blockade::Blockade() {};

Blockade::Blockade(const Blockade& d) : Order(d) {}

Blockade& Blockade::operator=(const Blockade& d) {
	Order::operator=(d);
	return *this;
}

string Diplomacy::getName() const {
	if (*ex) {
		return "The Diplomacy order has been executed, both players cannot attack each other";
	}
	else {
		return "This is a Diplomacy order";
	}
}

bool Diplomacy::validate() {
	if (1)
		return true;
};
void Diplomacy::execute() {
	*ex = validate();
};
Diplomacy::Diplomacy() {};

Diplomacy::Diplomacy(const Diplomacy& d) : Order(d) {}

Diplomacy& Diplomacy::operator=(const Diplomacy& d) {
	Order::operator=(d);
	return *this;
}

OrderList::OrderList() {
	list = vector<Order*>();
}

OrderList::OrderList(const OrderList& d) {
	list = vector<Order*>();

	copy(d.list.begin(), d.list.end(), back_inserter(list));  // copy each element from d.list into the list of the new object
}

OrderList& OrderList::operator =(const OrderList& e) {
	list = vector<Order*>(e.list);
	return *this;
}
OrderList::~OrderList() {  //destructor, deletes every pointer object from the list

	for (int i = 0; i < (int)list.size(); i++) {
		delete list.at(i);
	}
}

void OrderList::remove(int ind) {
	if (ind < 0 || ind >(int) list.size()) {
		cout << "Incorrect index number was passed, no changes will be made" << endl;
	}
	else {
		list.erase(list.begin() + ind);
	}
};

void OrderList::move(int ind, int final) {
	if (ind < 0 || ind >(int) list.size() || final < 0 || final >(int) list.size()) {
		cout << "Incorrect index number was passed, no changes will be made" << endl;
	}
	else {
		cout << "Moving order at index " << ind << " to index " << final << endl;
		Order* temp = list.at(ind);
		remove(ind);
		list.insert(list.begin() + final, temp);
	}

};

