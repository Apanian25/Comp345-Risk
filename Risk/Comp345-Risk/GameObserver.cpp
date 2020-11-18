#include "GameObserver.h"
#include "GameEngine.h"
#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include <iostream>
#include <list>
#include <vector>


Observer::Observer() {

}



Observer::~Observer() {

}



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
			(*i)->updatePhase();

		}
	}
}
void PhaseObserver::update(Player* player, string phase)
{
	cout << "Player " << player->player_name << ":" << phase << endl;
}

StatsObserver::StatsObserver(Player* p, Map* map) {
	
	player = p;
	player->Attach(this);
	updatePercentage(map);
 }

StatsObserver::~StatsObserver() {
	
	player->Detach(this);
}

void StatsObserver::updatePercentage(Map* map) {
this->occupiedPercentage = (float)(player->territories.size()) / map->getAllTerritories().size() * 100;
}


void StatsObserver::update() {

	if (occupiedPercentage == float(0)) {

		cout << (player->player_name) << " controls 0.0% of the world. Player "<<player->player_name <<" is ejected from the game" << endl;
		this->player->Detach(this);
	}

	else if (occupiedPercentage == float(100)) {
		cout << (player->player_name) << " controls " << occupiedPercentage << "%  of the word. won the game!" << endl;
	
	}
	else
		cout << (player->player_name) << " controls " << occupiedPercentage << "%  of the word." << endl;
}

void StatsObserver::updatePhase()
{

}



