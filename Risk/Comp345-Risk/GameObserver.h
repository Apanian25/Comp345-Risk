#pragma once
#include <list>
#include <iostream>
#include <vector>
using namespace std;


/*
* Create instances of the GameEnigne and the Player class
*/
class Map;
class GameEngine;
class Player;


/*
	Creates an interface basically for the observers
*/
class Observer {

public:
	virtual void update() = 0;
	virtual void update(string update) = 0;
	Observer();
	~Observer();
};


/*
	Subject class for the design pattern
*/
class Subject {
public:
	void Detach(Observer* ob);
	void Attach(Observer* ob);
	void Notify();
	void Notify(string update);
	Subject();
	~Subject();

protected:
	vector<Observer*> *obs;
};


/*
	Inherits and implements the observer class, used for the phases
*/
class PhaseObserver : public Observer {
	Player* player;
public:
	void update();
	void update(string message);
	PhaseObserver(Player* player);
	~PhaseObserver();
};

class StatsObserver : public Observer {
	int sizeOfMap;
public:
	StatsObserver(int sizeofMap);
	StatsObserver();
	~StatsObserver();
	double updatePercentage(Player* player);
	void update();
	void update(string message);
	void updatePhase();
	void setSizeOfMap(int sizeofMap);
};

