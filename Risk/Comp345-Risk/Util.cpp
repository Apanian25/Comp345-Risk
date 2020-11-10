#include "Player.h"
#include "Map.h"
#include "Util.h"
#include <vector>

void Util::init (std::vector<Player*> p) {
	players = p;
}

void Util::updatePlayers(vector<Player*> p) {
	players = p;
}

/// <summary>
/// 
/// </summary>
/// <param name="id">Player id</param>
/// <param name="territory">Territory to remove</param>
void Util::removeTerritory(int id, Territory* territory) {
	for (Player* p : players)
	{
		if (p->id == id) {
			p->territories.erase(std::remove(p->territories.begin(), p->territories.end(), territory), p->territories.end());
		}
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="id">Player id</param>
/// <param name="territory">Territory to add</param>
/// <param name="numOfArmies">new number of armies on the territory</param>
void Util::addTerritory(int id, Territory* territory, int numOfArmies) {
	for (Player* p : players) {
		if (p->id = id) {
			p->territories.push_back(territory);	
			territory->numberOfArmies = numOfArmies; //update number of armies for the territory
		}
	}
}