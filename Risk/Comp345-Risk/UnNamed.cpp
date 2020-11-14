#include "Map.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <map>

Map gameMap;
vector<Player*> players;
void removePlayersWithoutTerritories();
void reinforcementPhase();
void issueOrderPhase(vector<Order*>& deploy, vector<Order*>& otherOrders);
void ordersExecutionPhase(vector<Order*>& deploy, vector<Order*>& otherOrders);


int mainGameLoop() {
	do {
		vector<Order*> deploy;
		vector<Order*> otherOrders;
		removePlayersWithoutTerritories();
		reinforcementPhase();
		issueOrderPhase(deploy, otherOrders);
		ordersExecutionPhase(deploy, otherOrders);
	} while (true);
}

void removePlayersWithoutTerritories() {
	for (Player* player : players) {
		if (player->getTerritories().size() == 0) {
			//erase
		}
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
	
}