#include "Map.h"
#include <list>
#include <vector>
#include <iostream>
#include <map>
#include <queue>

class Map {
	int size;
	std::map<int, Territory*> territories;

	Map() {
		size = 0;
	}

	~Map() {
		for (std::pair<int, Territory*> territory : territories) {
			delete territory.second;
		}
	}

	/// <summary>
	/// Adds a territory to the Map
	/// </summary>
	/// <param name="id">The name of the territory</param>
	/// <param name="name">The name of the territory</param>
	Territory* addTerritory(int id, std::string name, std::string continent) {
		size++;
		Territory* territory = new Territory{ name, continent, id };
		territories[id] = territory;
		return territory;
	}

	/// <summary>
	/// Adds the dest's to the src's adjacency list
	/// </summary>
	/// <param name="src">source, the initial vertex</param>
	/// <param name="dest">destinations, an array of the arrival vertices</param>
	void addEdges(int src, int dest[]) {
		Territory* srcTerritory, * destTerritory;
		srcTerritory = territories.at(src);
		for (int i = 0; i < sizeof(dest); i++) {
			destTerritory = territories.at(dest[i]);
			srcTerritory->adjacentTerritoriesTo.push_back(destTerritory);
			destTerritory->adjacentTerritoriesFrom.push_back(srcTerritory);
		}
	}

	/// <summary>
	/// Adds the dest to the src's adjacency list
	/// </summary>
	/// <param name="src">source, the initial vertex</param>
	/// <param name="dest">destination, the arrival vertex</param>
	void addEdge(int src, int dest) {
		Territory* srcTerritory, * destTerritory;
		srcTerritory = territories.at(src);
		destTerritory = territories.at(dest);

		srcTerritory->adjacentTerritoriesTo.push_back(destTerritory);
		destTerritory->adjacentTerritoriesFrom.push_back(srcTerritory);
	}

	Territory* getTerritory(int id) {
		return territories[id];
	}

	/// <summary>
	/// Validates that the Map is a connected graph
	/// The validation is done using a variation of a depth first search
	/// </summary>
	/// <returns>boolean true if the Map is a conencted graph, false otherwise</returns>
	bool validate() {
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
};