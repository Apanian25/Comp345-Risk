#include<iostream>
#include <string>
#include "Orders.h"
#include "Cards.h"
#include "Map.h"
#include "Player.h"
//#include "Util.h";
#include <algorithm>
#include <time.h>
#include "GameEngine.h"

using namespace std;
gameEngine* engine = new gameEngine();
/// <summary>
/// This constructor initializes isExecuted to false.
/// </summary>
Order::Order() {
	isExecuted = false; //this is the boolean member that checks if an order has been executed
};
/// <summary>
/// This copy constructor takes an Order object and copies the isExecuted boolean into the new object
/// </summary>
/// <param name="a">a is an Order Object </param>
Order::Order(const Order& a) {
	isExecuted = a.isExecuted;
}

/// <summary>
/// This destructor is left empty as there are no pointer data members, compiler will delete anything on the stack
/// </summary>
Order::~Order() { };
/// <summary>
/// This virtual method is used to execute an order, Order is the base class and not an actual specific order so it is left empty
/// </summary>
void Order::execute() {};

/// <summary>
/// This virtual method is used in the stream insertion operator to print the information, Order is the base class and not an actual specific Order
/// </summary>
/// <returns>The information on the order</returns>
string Order::getName() const {
	return "This is an unspecified order ";
}
/// <summary>
/// This is the stream insertion operator 
/// </summary>
/// <returns> The string from getName() </returns>
std::ostream& operator<<(std::ostream& stream, const  Order& e)
{
	return stream << e.getName();
}
/// <summary>
/// This is the assignement operator
/// </summary>
/// <param name="a"> a is an Order object </param>
/// <returns>Assigns the same data members as a</returns>
Order& Order::operator=(const Order& a) {
	isExecuted = a.isExecuted;
	return *this;
}
/// <summary>
/// This method overrides the base class method and checks isExecuted to output the right information
/// </summary>
/// <returns>The information on the Deploy object</returns>
string Deploy::getName() const {
	if (isExecuted) {									//returns a different string depending on ex
		return "The Deploy order has been executed, armies are on the territory";
	}
	else {
		return "This is a Deploy order";
	}
}
/// <summary>
/// This method validates an order, since there is no game implementation yet, just return true
/// </summary>
/// <returns>true</returns>
bool Deploy::validate() {
	return territoryPtr->ownedBy == playerPtr->id;
}

/// <summary>
/// This method executes an order, changing isExecuted to true
/// </summary>
void Deploy::execute() 
{
	isExecuted = validate();
	if (isExecuted)
	{
		territoryPtr->addArmies(numOfArmies);
		cout << getName() << endl;
	}
	
};
/// <summary>
/// This constructor is empty as there are no data members to Deploy
/// </summary>
Deploy::Deploy() {}


Deploy::Deploy(Player* p, Territory* t, int numOfArmies)
{
	this->playerPtr = p;
	this->territoryPtr = t;
	this->numOfArmies = numOfArmies;
};

/// <summary>
/// This copy constructor first makes a call to the base class Order copy contructor 
/// </summary>
/// <param name="d">d is a Deploy object</param>
Deploy::Deploy(const Deploy& d) : Order(d) {}

/// <summary>
/// This destructor is left empty as there are no pointer data members, compiler will delete anything on the stack
/// </summary>
Deploy::~Deploy() {};

/// <summary>
/// This is the assignement operator that first calls the assignement operator in the base class Order
/// </summary>
/// <param name="d">d is a Deploy object</param>
/// <returns>The same data members as d</returns>
Deploy& Deploy::operator=(const Deploy& d) {
	Order::operator=(d);
	return *this;
}

/// <summary>
/// This method overrides the base class method and checks isExecuted to output the right information
/// </summary>
/// <returns>The information on the Bomb object</returns>
string Bomb::getName() const {
	if (isExecuted) {
		return "The Bomb order has been executed, half of enemy armies are eliminated";
	}
	else {
		return "This is a Bomb order";
	}
}
/// <summary>
/// This method validates an order, since there is no game implementation yet, just return true
/// </summary>
/// <returns>true</returns>
bool Bomb::validate()
{
	return target->ownedBy != player1->id;
};
/// <summary>
/// This method executes an order, changing isExecuted to true
/// </summary>
void Bomb::execute() {
	isExecuted = validate();
	if (isExecuted)
	{
		target->removeArmies(target->numberOfArmies / 2);
	}
	
};
/// <summary>
/// This constructor is empty as there are no data members to Bomb
/// </summary>
Bomb::Bomb() {};

Bomb::Bomb(Player* p1, Territory* target) //TODO : mAYBE REMOVE PLAYER 2
{
	this->player1 = p1;
	this->target = target;
	
}
/// <summary>
/// This copy constructor first makes a call to the base class Order copy contructor 
/// </summary>
/// <param name="d">d is a Bomb object</param>
Bomb::Bomb(const Bomb& d) : Order(d) {};

/// <summary>
/// This destructor is left empty as there are no pointer data members, compiler will delete anything on the stack
/// </summary>
Bomb::~Bomb() { };

/// <summary>
/// This is the assignement operator that first calls the assignement operator in the base class Order
/// </summary>
/// <param name="d">d is a Bomb object</param>
/// <returns>The same data members as d</returns>
Bomb& Bomb::operator=(const Bomb& d) {
	Order::operator=(d);
	return *this;
}
/// <summary>
/// This method overrides the base class method and checks isExecuted to output the right information
/// </summary>
/// <returns>The information on the Airlift object</returns>
string Airlift::getName() const {
	if (isExecuted) {
		return "The Airlift order has been executed, armies are on the territory";
	}
	else {
		return "This is a Airlift order";
	}
}
/// <summary>
/// This method validates an order, since there is no game implementation yet, just return true
/// </summary>
/// <returns>true</returns>
bool Airlift::validate() {
	if (playerPtr->hasNegotiatedWithId == target->ownedBy)
		return false;
	bool playerOwnsSrcTerritory = source->ownedBy == playerPtr->id;
	option = !playerOwnsSrcTerritory ? -1 : target->ownedBy == playerPtr->id ? 1 : 2;
	return playerOwnsSrcTerritory;
};
/// <summary>
/// This method executes an order, changing isExecuted to true
/// </summary>
void Airlift::execute() {
	//std::vector<Player*> players; // TODO : REMOVE
	srand(time(NULL));
	isExecuted = validate();

	if (isExecuted)
	{
		if (option == 1)
		{
			target->addArmies(numOfArmies);
			source->removeArmies(numOfArmies);

		}
		else if (option == 2)
		{
			int attackingArmiesCount = numOfArmies;
			int defendingArmiesdestroyed = 0;
			int defendingArmiesCount = target->numberOfArmies;
			int attackingArmiesdestroyed = 0;
			int randomizer = rand() % 10 + 1;

			for (int i = 1; i <= numOfArmies; i++)
			{
				int low = 1;
				int high = 6;

				if (randomizer >= 1 && randomizer <= 6)
				{
					cout << "defending army destroyed" << endl;
					defendingArmiesCount--;
					defendingArmiesdestroyed++;
				}
				else
				{
					cout << "defending army survived" << endl;
				}
			}

			for (int i = 1; i <= target->numberOfArmies; i++)
			{
				int low = 1;
				int high = 7;

				if (randomizer >= 1 && randomizer <= 7)
				{
					cout << "attacking army destroyed" << endl;
					attackingArmiesCount--;
					attackingArmiesdestroyed++;

				}
				else
				{
					cout << "attacking army survived" << endl;
				}
			}
			
			if (defendingArmiesCount < 0)
			{
				defendingArmiesCount = 0;
			}
			if (attackingArmiesCount < 0)
			{
				attackingArmiesCount = 0;
			}
			
			if (defendingArmiesCount == 0 && attackingArmiesCount > 0)
			{
				for (Player* p : players)
				{
					if (p->id == target->ownedBy) {
						p->territories.erase(std::remove(p->territories.begin(), p->territories.end(), target), p->territories.end());
					}
				}

				playerPtr->territories.push_back(target);
				target->numberOfArmies = attackingArmiesCount;
				target->ownedBy = playerPtr->id;
				source->numberOfArmies -= numOfArmies;

				playerPtr->hasConqueredTerritory = true;
			}

			else if ((attackingArmiesCount == 0 && defendingArmiesCount != 0) || (attackingArmiesCount != 0 && defendingArmiesCount != 0) || (attackingArmiesCount == 0 && defendingArmiesCount == 0))
			{
				source->numberOfArmies -= attackingArmiesdestroyed;
				target->numberOfArmies -= defendingArmiesdestroyed;
			}
			
		}
	}

};
/// <summary>
/// This constructor is empty as there are no data members to Airlift
/// </summary>
Airlift::Airlift() {};

Airlift::Airlift(Player* p, Territory* s, Territory* t, int numOfArmies)
{
	this->playerPtr = p;
	this->source = s;
	this->target = t;
	this->numOfArmies = numOfArmies;
	this->option = 0;
}

/// <summary>
/// This copy constructor first makes a call to the base class Order copy contructor 
/// </summary>
/// <param name="d">d is a Airlift object</param>
Airlift::Airlift(const Airlift& d) : Order(d) {}

/// <summary>
/// This destructor is left empty as there are no pointer data members, compiler will delete anything on the stack
/// </summary>
Airlift::~Airlift() {};

/// <summary>
/// This is the assignement operator that first calls the assignement operator in the base class Order
/// </summary>
/// <param name="d">d is a Airlift object</param>
/// <returns>The same data members as d</returns>
Airlift& Airlift::operator=(const Airlift& d) {
	Order::operator=(d);
	return *this;
}
/// <summary>
/// This method overrides the base class method and checks isExecuted to output the right information
/// </summary>
/// <returns>The information on the Advance object</returns>
string Advance::getName() const {
	if (isExecuted) {
		return "The Advance order has been executed, armies are on the territory";
	}
	else {
		return "This is a Advance order";
	}
}
/// <summary>
/// This method validates an order, since there is no game implementation yet, just return true
/// </summary>
/// <returns>true</returns>
bool Advance::validate() {// need to fix
	if (source->ownedBy == playerPtr->id) {
		if (playerPtr->hasNegotiatedWithId == adjacent->ownedBy) 
		{
			cout << " Can't attack under diplomacy act" << endl;
				return false;
		}
			
		for (Territory* t : source->adjacentTerritoriesTo) {
			if (t->id == adjacent->id) {
				option = adjacent->ownedBy == playerPtr->id ? 1 : 2;
				return true;
			}
		}
	}
	return false;
};
/// <summary>
/// This method executes an order, changing isExecuted to true
/// </summary>
void Advance::execute() {
	//std::vector<Player*> players; // TODO : REMOVE
	srand(time(NULL));
	isExecuted = validate();
	if (isExecuted)
	{
		if (option == 1)
		{
			adjacent->addArmies(numOfArmies);
			source->removeArmies(numOfArmies);
			
		}
		else if (option == 2)
		{
			int attackingArmiesCount = numOfArmies;
			int defendingArmiesdestroyed = 0;
			int defendingArmiesCount = adjacent->numberOfArmies;
			int attackingArmiesdestroyed = 0;
			//int randomizer = rand() % 10 + 1;
			for (int i = 0; i < numOfArmies; i++)
			{
				int randomizer = rand() % 10 + 1;
				cout << randomizer;
				if (randomizer >= 1 && randomizer <= 6)
				{
					cout << "defending army destroyed" << endl;
					defendingArmiesCount--;
					defendingArmiesdestroyed++;
					
				}
				else
				{
					cout << "defending army survived" << endl;
				}
			}
			for (int i = 0; i < adjacent->numberOfArmies; i++)
			{
				int randomizer = rand() % 10 + 1;
				cout << randomizer;
				if (randomizer >= 1 && randomizer <= 7)
				{
					
					cout << "attacking army destroyed" << endl;
					attackingArmiesCount--;
					attackingArmiesdestroyed++;
					
				}
				else
				{
					cout << "attacking army survived" << endl;
				}
			}

			if (defendingArmiesCount < 0)
			{
				defendingArmiesCount = 0;
			}
			if (attackingArmiesCount < 0)
			{
				attackingArmiesCount = 0;
			}
			
			if (defendingArmiesCount == 0 && attackingArmiesCount > 0)
			{
				
				for (Player * p : players)
				{
					if (p->id == adjacent->ownedBy) {
						p->territories.erase(std::remove(p->territories.begin(), p->territories.end(), adjacent), p->territories.end());
					}
				}

				playerPtr->territories.push_back(adjacent);
				adjacent->numberOfArmies = attackingArmiesCount;
				adjacent->ownedBy = playerPtr->id;
				source->numberOfArmies -= numOfArmies;
				
				playerPtr->hasConqueredTerritory = true;
				
			}
			else if ((attackingArmiesCount == 0 && defendingArmiesCount != 0) || (attackingArmiesCount != 0 && defendingArmiesCount != 0) || (attackingArmiesCount == 0 && defendingArmiesCount == 0))
			{
				source->numberOfArmies -= attackingArmiesdestroyed;
				adjacent->numberOfArmies -= defendingArmiesdestroyed;
			}
		} 
	}
};
/// <summary>
/// This constructor is empty as there are no data members to Advance
/// </summary>
Advance::Advance() {
	this->option = -1;
	this->playerPtr = NULL;
	this->source = NULL;
	this->adjacent = NULL;
	this->numOfArmies = -1;
};

Advance::Advance(Player* p, Territory* source, Territory* target, int numOfArmies)
{
	this->option = -1;
	this->playerPtr = p;
	this->source = source;
	this->adjacent = target;
	this->numOfArmies = numOfArmies;
}

/// <summary>
/// This copy constructor first makes a call to the base class Order copy contructor 
/// </summary>
/// <param name="d">d is a Advance object</param>
Advance::Advance(const Advance& d) : Order(d) {}

/// <summary>
/// This destructor is left empty as there are no pointer data members, compiler will delete anything on the stack
/// </summary>
Advance::~Advance() {};

/// <summary>
/// This is the assignement operator that first calls the assignement operator in the base class Order
/// </summary>
/// <param name="d">d is a Advance object</param>
/// <returns>The same data members as d</returns>
Advance& Advance::operator=(const Advance& d) {
	Order::operator=(d);
	return *this;
}
/// <summary>
/// This method overrides the base class method and checks isExecuted to output the right information
/// </summary>
/// <returns>The information on the Blockade object</returns>
string Blockade::getName() const {
	if (isExecuted) {
		return "The Blockade order has been executed, the number of armies has tripled and the territory is neutral";
	}
	else {
		return "This is a Blockade order";
	}
}
/// <summary>
/// This method validates an order, since there is no game implementation yet, just return true
/// </summary>
/// <returns>true</returns>
bool Blockade::validate() {
	return target->ownedBy == playerPtr->id;
	//std::cout << "invalid order, player does not own target territory, please select another" << std::endl;
};

/// <summary>
/// This method executes an order, changing isExecuted to true
/// </summary>
void Blockade::execute() { 

	isExecuted = validate();
	if (isExecuted)
	{
		target->addArmies(target->numberOfArmies);

		playerPtr->territories.erase(std::remove(playerPtr->territories.begin(), playerPtr->territories.end(), target), playerPtr->territories.end());
		target->ownedBy = -1;
		
	}

};
/// <summary>
/// This constructor is empty as there are no data members to Blockade
/// </summary>
Blockade::Blockade() {};

Blockade::Blockade(Player* p, Territory* t)
{
	this->playerPtr = p;
	this->target = t;
}

/// <summary>
/// This copy constructor first makes a call to the base class Order copy contructor 
/// </summary>
/// <param name="d">d is a Blockade object</param>
Blockade::Blockade(const Blockade& d) : Order(d) {}

/// <summary>
/// This destructor is left empty as there are no pointer data members, compiler will delete anything on the stack
/// </summary>
Blockade::~Blockade() {};

/// <summary>
/// This is the assignement operator that first calls the assignement operator in the base class Order
/// </summary>
/// <param name="d">d is a Blockade object</param>
/// <returns>The same data members as d</returns>
Blockade& Blockade::operator=(const Blockade& d) {
	Order::operator=(d);
	return *this;
}
/// <summary>
/// This method overrides the base class method and checks isExecuted to output the right information
/// </summary>
/// <returns>The information on the Diplomacy object</returns>
string Diplomacy::getName() const {
	if (isExecuted) {
		return "The Diplomacy order has been executed, both players cannot attack each other";
	}
	else {
		return "This is a Diplomacy order";
	}
}
/// <summary>
/// This method validates an order, since there is no game implementation yet, just return true
/// </summary>
/// <returns>true</returns>
bool Diplomacy::validate() {
	
		if (player1->id != player2->id)
		{
			return true;
		}
		
		return false;
};
/// <summary>
/// This method executes an order, changing isExecuted to true
/// </summary>
void Diplomacy::execute() {
	isExecuted = validate();
	if (isExecuted)
	{
		player1->hasNegotiatedWithId = player2->id;
		player2->hasNegotiatedWithId = player1->id;
	}
};
/// <summary>
/// This constructor is empty as there are no data members to Diplomacy
/// </summary>
Diplomacy::Diplomacy() {};

Diplomacy::Diplomacy(Player* p1, Player* p2)
{
	this->player1 = p1;
	this->player2 = p2;
}

/// <summary>
/// This copy constructor first makes a call to the base class Order copy contructor 
/// </summary>
/// <param name="d">d is a Diplomacy object</param>
Diplomacy::Diplomacy(const Diplomacy& d) : Order(d) {}

/// <summary>
/// This destructor is left empty as there are no pointer data members, compiler will delete anything on the stack
/// </summary>
Diplomacy::~Diplomacy() {};

/// <summary>
/// This is the assignement operator that first calls the assignement operator in the base class Order
/// </summary>
/// <param name="d">d is a Diplomacy object</param>
/// <returns>The same data members as d</returns>
Diplomacy& Diplomacy::operator=(const Diplomacy& d) {
	Order::operator=(d);
	return *this;
}


Reinforcement::Reinforcement() {}
Reinforcement::~Reinforcement() {}
Reinforcement::Reinforcement(Reinforcement const& r) {}
void Reinforcement::execute() {}
string Reinforcement::getName() const { return "Reinforcement"; }
Reinforcement& Reinforcement::operator=(const Reinforcement& r) { return *this; }

/// <summary>
/// This constructor initializes list to a vector of pointer Objects
/// </summary>
OrderList::OrderList() {
	list = vector<Order*>();
}
/// <summary>
/// This copy construtor copiesc each element from d.list into the list of the new OrderList
/// </summary>
/// <param name="d">d is a OrderList object</param>
OrderList::OrderList(const OrderList& d) {
	list = vector<Order*>();

	copy(d.list.begin(), d.list.end(), back_inserter(list));  
}

OrderList& OrderList::operator =(const OrderList& e) {
	list = vector<Order*>(e.list);
	return *this;
} 
/// <summary>
/// This destructor deletes every pointer object from the list
/// </summary>
OrderList::~OrderList() {

	for (int i = 0; i < (int)list.size(); i++) {
		delete list.at(i);
	}
}
/// <summary>
/// This remove method verifies if ind is a valid index number. If so, it removes the element at index ind from list
/// </summary>
/// <param name="ind">ind is the index number of the Odder we want to remove from list</param>
void OrderList::remove(int ind) {
	if (ind < 0 || ind >(int) list.size()) {
		cout << "Incorrect index number was passed, no changes will be made" << endl;
	}
	else {
		list.erase(list.begin() + ind);
	}
};
/// <summary>
/// This move mthod verifies if ind and fin are valid index numbers. If so, remove the Object at the ind index, and insert it in the fin index
/// </summary>
/// <param name="ind">ind is the index of the Object we want to move</param>
/// <param name="fin">fin is the index where we place the Order of ind</param>
void OrderList::move(int ind, int fin) {
	if (ind < 0 || ind >(int) list.size() || fin < 0 || fin >(int) list.size()) {
		cout << "Incorrect index number was passed, no changes will be made" << endl;
	}
	else {
		cout << "Moving order at index " << ind << " to index " << fin << endl;
		Order* temp = list.at(ind);
		remove(ind);
		list.insert(list.begin() + fin, temp);
	}

};

