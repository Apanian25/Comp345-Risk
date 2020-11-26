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

	Subject(const Subject& subj);
	friend ostream& operator << (ostream& out, const Subject& observer);
	Subject& operator = (const Subject& observer);

	~Subject();



protected:
	vector<Observer*> obs;
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

	PhaseObserver(const PhaseObserver& observer);
	friend ostream& operator << (ostream& out, const PhaseObserver& observer);
	PhaseObserver& operator = (const PhaseObserver& observer);

	~PhaseObserver();
};

class StatsObserver : public Observer {
	int sizeOfMap;
public:
	StatsObserver(int sizeofMap);
	StatsObserver();

	StatsObserver(const StatsObserver& observer);
	friend ostream& operator << (ostream& out, const StatsObserver& observer);
	StatsObserver& operator = (const StatsObserver& observer);

	~StatsObserver();
	double updatePercentage(Player* player);
	void update();
	void update(string message);
	void updatePhase();
	void setSizeOfMap(int sizeofMap);
};

