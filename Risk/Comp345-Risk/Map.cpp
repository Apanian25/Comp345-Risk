#include "Map.h"
#include <list>
#include <vector>
#include <iostream>
#include <map>
#include <queue>


//CONTINENT
Continent::Continent() : id(-1), numberOfArmies(-1), name("") {}

Continent::Continent(std::string name, int id, int numberOfArmies): name(name), id(id), numberOfArmies(numberOfArmies) {}

Continent::~Continent() { }

Continent::Continent(const Continent& continent): id(continent.id), numberOfArmies(continent.numberOfArmies), name(continent.name) {}

Continent& Continent::operator= (const Continent& continent) {
	id = continent.id;
	numberOfArmies = continent.numberOfArmies;
	name = continent.name;

	return *this;
}

std::ostream & operator << (std::ostream & output, const Continent& continent) {
	output << "ID: " << continent.id << std::endl
		<< "NAME: " << continent.name << std::endl
		<< "NUMBER OF ARMIES(BONUS): " << continent.numberOfArmies << std::endl;

	return output;
}


//TERRITORY
Territory::Territory(): id(-1), ownedBy(-1), continentId(-1), country(""){ }

Territory::Territory(std::string country, int id, int continentId): id(id), continentId(continentId), country(country), ownedBy(-1) { }

Territory::~Territory() {};

Territory::Territory(const Territory& territory): id(territory.id), continentId(territory.continentId), country(territory.country) {
	this->adjacentTerritoriesFrom = territory.adjacentTerritoriesFrom;
	this->adjacentTerritoriesTo = territory.adjacentTerritoriesTo;
}

Territory& Territory::operator= (const Territory& territory) {
	id = territory.id;
	country = territory.country;
	continentId = territory.continentId;
	ownedBy = territory.ownedBy;
	adjacentTerritoriesFrom = territory.adjacentTerritoriesFrom;
	adjacentTerritoriesTo = territory.adjacentTerritoriesTo;

	return *this;
}

std::ostream& operator << (std::ostream& output, const Territory& territory) {
	output << "ID: " << territory.id << std::endl
		<< "Country: " << territory.country << std::endl
		<< "OWNED BY: " << territory.ownedBy << std::endl
		<< "CONTINENT ID: " << territory.continentId << std::endl
		<< "CAN ATTACK:" << std::endl;

	for (Territory* to : territory.adjacentTerritoriesTo) {
		output << "\t" << to->country <<std::endl;
	}

	output << "CAN BE ATTACKED BY:" << std::endl;
	for (Territory* from : territory.adjacentTerritoriesFrom) {
		output << "\t" << from->country << std::endl;
	}

	return output;
}


//MAP
Map::Map() { }

Map::Map(const Map& map) {
	for (std::pair<int, Territory*> territory : map.territories) {
		this->territories[territory.first] = new Territory(*(territory.second));
	}

	for (std::pair<int, Continent*> continent : continents) {
		this->continents[continent.first] = new Continent(*(continent.second));
	}

	for (std::pair<int, std::vector<Territory*>> continent : map.continentTerritories) {
		for (Territory* territory : continent.second) {
			this->continentTerritories[continent.first].push_back(territory);
		}
	}
}

Map::~Map() {
	for (std::pair<int, Territory*> territory : territories) {
		delete territory.second;
		territory.second = NULL;
	}
	for (std::pair<int, Continent*> continent : continents) {
		delete continent.second;
		continent.second = NULL;
	}

	for (std::pair<int, std::vector<Territory*>> continent : continentTerritories) {
		for (Territory* territory : continent.second) {
			territory = NULL;
		}
	}
}

Map& Map::operator= (const Map& map) {
	this->territories = map.territories;
	this->continents = map.continents;
	this->continentTerritories = map.continentTerritories;
}

std::ostream& operator << (std::ostream& output, const Map& map) {

	for (std::pair<int, std::vector<Territory*>> continent : map.continentTerritories) {
			output << "Continent: " << map.continents.find(continent.first)->second->name << std::endl;
		for (Territory* territory : continent.second) {
		}
	}
}

Territory* Map::getTerritory(int id) {
	return territories[id];
}

/// <summary>
/// Adds a territory to the Map
/// </summary>
/// <param name="id">The name of the territory</param>
/// <param name="name">The name of the territory</param>
Territory* Map::addTerritory(std::string country, int id, int continentId) {
	Territory* territory = new Territory(country, id, continentId);
	territories[id] = territory;
	continentTerritories[continentId].push_back(territory);
	return territory;
}

Continent* Map::addContinent(std::string continent, int continentId, int numberOfArmies) {
	Continent *newContinent = new Continent(continent, continentId, numberOfArmies);
	continents[continentId] = newContinent;

	return newContinent;
}

/// <summary>
/// Adds the dest's to the src's adjacency list
/// </summary>
/// <param name="src">source, the initial vertex</param>
/// <param name="dest">destinations, an array of the arrival vertices</param>
void Map::addEdges(int src, std::vector<int> dest) {
	Territory* srcTerritory, * destTerritory;
	srcTerritory = territories[src];
	for (int index : dest) {
		destTerritory = territories[index];
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