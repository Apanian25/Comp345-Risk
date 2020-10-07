#include "Map.h"
#include <list>
#include <vector>
#include <iostream>
#include <map>
#include <queue>


Map::Map() {
	size = 0;
}

Map::~Map() {
	for (std::pair<int, Territory*> territory : territories) {
		delete territory.second;
	}
}

/// <summary>
/// Adds a territory to the Map
/// </summary>
/// <param name="id">The name of the territory</param>
/// <param name="name">The name of the territory</param>
Territory* Map::addTerritory(int id, int numberOfArmies, std::string name, std::string continent) {
	size++;
	Territory* territory = new Territory{ name, continent, id, numberOfArmies };
	territories[id] = territory;
	return territory;
}

/// <summary>
/// Adds the dest's to the src's adjacency list
/// </summary>
/// <param name="src">source, the initial vertex</param>
/// <param name="dest">destinations, an array of the arrival vertices</param>
void Map::addEdges(int src, int dest[]) {
	Territory* srcTerritory, * destTerritory;
	srcTerritory = territories[src];
	for (int i = 0; i < (sizeof(dest)/sizeof(int)); i++) {
		destTerritory = territories[dest[i]];
		srcTerritory->adjacentTerritoriesTo.push_back(destTerritory);
		destTerritory->adjacentTerritoriesFrom.push_back(srcTerritory);
	}
}

/// <summary>
/// Adds the dest to the src's adjacency list
/// </summary>
/// <param name="src">source, the initial vertex</param>
/// <param name="dest">destination, the arrival vertex</param>
void Map::addEdge(int src, int dest) {
	Territory* srcTerritory, * destTerritory;
	srcTerritory = territories[src];
	destTerritory = territories[dest];

	srcTerritory->adjacentTerritoriesTo.push_back(destTerritory);
	destTerritory->adjacentTerritoriesFrom.push_back(srcTerritory);
}

Territory* Map::getTerritory(int id) {
	return territories[id];
}

/// <summary>
/// Validates that the Map is a connected graph
/// The validation is done using a variation of a depth first search
/// </summary>
/// <returns>boolean true if the Map is a conencted graph, false otherwise</returns>
bool Map::validate() {
	std::vector<int> visited;
	std::queue<Territory*> queue;
	queue.push(territories.begin()->second);

	while (!queue.empty()) {
		Territory* territory = queue.front();
		if (std::count(visited.begin(), visited.end(), territory->id) == 0) {
			//this node/territory has not been visited 
			for (Territory* to : territory->adjacentTerritoriesTo) {
				queue.push(to);
			}
			for (Territory* from : territory->adjacentTerritoriesFrom) {
				queue.push(from);
			}
			visited.push_back(territory->id);
		}
		queue.pop();
	}

	for (std::pair<int, Territory*> territory : territories) {
		if (std::count(visited.begin(), visited.end(), territory.first) == 0) {
			//this id has not been visited, this means graph is not connected
			return false;
		}
	}

	return true;
}
