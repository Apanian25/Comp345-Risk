#include "Map.h"
#include "Player.h"
#include "GameEngine.h";
#include <iostream>
#include <vector>
#include <map>

Map gameMap;
void removePlayersWithoutTerritories();
void reinforcementPhase();
void issueOrderPhase(vector<Order*>& deploy, vector<Order*>& otherOrders);
void ordersExecutionPhase(vector<Order*>& deploy, vector<Order*>& otherOrders);
bool hasWinner();


int mainGameLoop() {
	do {
		vector<Order*> deploy;
		vector<Order*> otherOrders;
		removePlayersWithoutTerritories();
		reinforcementPhase();
		issueOrderPhase(deploy, otherOrders);
		ordersExecutionPhase(deploy, otherOrders);

		for (Player* player : players) {
			player->hasConqueredTerritory = false;
			//player->hasNegotiatedWithID = -500;
		}
	} while (hasWinner());
}

void removePlayersWithoutTerritories() {
	vector<Player*> playersToRemove;
	for (Player* player : players) {
		if (player->getTerritories().size() == 0) {
			playersToRemove.push_back(player);
		}
	}

	for (Player* player : playersToRemove) {
		players.erase(std::remove(players.begin(), players.end(), player));
	}
}

void issueOrderPhase(vector<Order*>& deploy, vector<Order*>& otherOrders) {
	for (Player* player : players) {
		while (true) {
			Order* order = player->issueOrder();
			if (order == NULL)
				break;
		}
	}
}

void reinforcementPhase() {
	std::map<int, std::vector<Territory*>> continentTerritories = gameMap.getContinentTerritories();
	std::map<int, Continent*> continents = gameMap.getContinents();

	for (Player* player : players) {
		int numberOfTerritorys = player->getTerritories().size();
		int bonusArmies{ numberOfTerritorys <= 9 ? 3 : numberOfTerritorys / 3 };
		
		
		for (pair<int, std::vector<Territory*>> continent : continentTerritories) {
			bool ownsContinent = true;
			for (Territory* territory: continent.second) {
				if (territory->ownedBy != player->id) {
					ownsContinent = false;
					break;
				}
			}
			if (ownsContinent) {
				bonusArmies += continents[continent.first]->numberOfArmies;
			}
		}
		player->giveArmies(bonusArmies);
	}
}

void ordersExecutionPhase(vector<Order*>& deploy, vector<Order*>& otherOrders) {
	//Deploy orders execute first
	for (Player* player : players) {
		vector<Order*> deploys;
		for (Order* order : player->orders) {
			if (dynamic_cast<Deploy*>(order)) {
				deploys.push_back(order);
			}
		}

		for (Order* order : deploys) {
			order->execute();
			delete order;
			player->orders.erase(std::remove(player->orders.begin(), player->orders.end(), order));
		}
	}

	//Other orders execute second.
	for (Player* player : players) {
		for (Order* order : player->orders) {
			order->execute();
			delete order;
		}

		player->orders.clear();
		if (player->hasConqueredTerritory) {
			player->hand->draw(*deck);
		}
	}
}

bool hasWinner() {
	map<int, Territory*> territories = gameMap.getAllTerritories();
	int point = territories.at(0)->ownedBy;
	for (pair<int, Territory*> territory : territories) {
		if (territory.second->ownedBy != point)
			return false;
	}

	return true;
}