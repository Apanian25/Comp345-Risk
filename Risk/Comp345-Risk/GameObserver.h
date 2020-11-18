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
	virtual void updatePhase() = 0;
	Observer();
	~Observer();



protected:
	

};

/*
	Subject class for the design pattern
*/

class Subject {

public:

	void Detach(Observer* ob);
	void Attach(Observer* ob);
	void Notify();
	Subject();
	~Subject();
	

protected:

	vector<Observer*> *obs;


};


/*
	Inherits and implements the observer class, used for the phases
*/
class PhaseObserver : public Observer {

private:
	int currentPlayer;


public:

	void update(Player* player, string phase) ;

};

class StatsObserver : public Observer {

public:
	StatsObserver(Player* p, Map* map);
	~StatsObserver();
	void updatePercentage(Map* map);
	void update();
	void updatePhase();


private:
	Player* player;
	float occupiedPercentage;
	
};

