#include "GameObserver.h"
#include "GameEngine.h"
#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include <iostream>
#include <list>
#include <vector>


Observer::Observer() {}
Observer::~Observer() {}

Subject::Subject() {

	obs = new vector<Observer*>();
}

Subject::~Subject() {
	delete obs;
}


void Subject::Attach(Observer* ob) {
	
	obs->push_back(ob);
}

void Subject::Detach(Observer* ob) {

	obs->erase(remove(obs->begin(), obs->end(), ob), obs->end());
}

void Subject::Notify() {
	if (obs->size() > 0) {
		vector<Observer*>::iterator i = obs->begin();
		for (; i != obs->end(); ++i) {
			(*i)->update();
		}
	}
}

void Subject::Notify(string update) {
	if (obs->size() > 0) {
		vector<Observer*>::iterator i = obs->begin();
		for (; i != obs->end(); ++i) {
			(*i)->update(update);
		}
	}
}


void PhaseObserver::update()
{
	cout << "Player " << player->player_name << ":" << player->getPhase() << endl;
}

void PhaseObserver::update(string update)
{
	this->update();
	cout << update << endl;
}


PhaseObserver::PhaseObserver(Player* player) : player(player) {
	player->Attach(this);
}

PhaseObserver::~PhaseObserver(){
	player->Detach(this);
}

StatsObserver::StatsObserver(int sizeOfMap) : sizeOfMap(sizeOfMap) {
	for (Player* player : players) {
		player->Attach(this);
	}
 }

StatsObserver::~StatsObserver() {
	for (Player* player : players) {
		player->Detach(this);
	}
}

double StatsObserver::updatePercentage(Player* player) {
	return (double)(player->territories.size()) /sizeOfMap * 100;
}


void StatsObserver::update() {
	cout << endl;
	for (Player* player : players) {
		double occupiedPercentage = updatePercentage(player);
		if (occupiedPercentage == double(0)) {

			cout << (player->player_name) << " controls 0.0% of the world. Player "<<player->player_name <<" is ejected from the game" << endl;
			player->Detach(this);
		}

		else if (occupiedPercentage == double(100)) {
			cout << (player->player_name) << " controls " << occupiedPercentage << "%  of the world. won the game!" << endl;
	
		}
		else
			cout << (player->player_name) << " controls " << occupiedPercentage << "%  of the world." << endl;
	}
	cout << endl;
}

void StatsObserver::update(string update) {
	this->update();
}

void StatsObserver::updatePhase()
{

}

StatsObserver::StatsObserver() : sizeOfMap(0)
{
	for (Player* player : players) {
		player->Attach(this);
	}
}
void StatsObserver::setSizeOfMap(int sizeOfMap)
{
	this->sizeOfMap = sizeOfMap;
}


void display() {
	
}
