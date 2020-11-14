#include "Map.h"
#include <list>
#include <vector>
#include <iostream>
#include <map>
#include <queue>


// *********************************************************** CONTINENT ***********************************************************

/// <summary>
/// Continent no-param constructor
/// </summary>
Continent::Continent() : id(-1), numberOfArmies(-1), name("") {}

/// <summary>
/// Constructor that sets name, id and number of armies
/// </summary>
/// <param name="name">the name of the continent</param>
/// <param name="id">the id of the continent</param>
/// <param name="numberOfArmies">The bonus number of armies that you get for conquering a continent</param>
Continent::Continent(std::string name, int id, int numberOfArmies): name(name), id(id), numberOfArmies(numberOfArmies) {}

/// <summary>
/// Destructor
/// </summary>
Continent::~Continent() { }

/// <summary>
/// Copy constructor 
/// </summary>
/// <param name="continent"></param>
Continent::Continent(const Continent& continent): id(continent.id), numberOfArmies(continent.numberOfArmies), name(continent.name) {}

/// <summary>
/// Overload of the assignment operator
/// </summary>
/// <param name="continent"></param>
/// <returns></returns>
Continent& Continent::operator= (const Continent& continent) {
	id = continent.id;
	numberOfArmies = continent.numberOfArmies;
	name = continent.name;

	return *this;
}

/// <summary>
/// This formats how the continent will be outputted when using cout << continent
/// </summary>
/// <param name="output"></param>
/// <param name="continent"></param>
/// <returns></returns>
std::ostream & operator << (std::ostream & output, const Continent& continent) {
	output << "ID: " << continent.id << std::endl
		<< "NAME: " << continent.name << std::endl
		<< "NUMBER OF ARMIES(BONUS): " << continent.numberOfArmies << std::endl;

	return output;
}


// *********************************************************** TERRITORY ***********************************************************

/// <summary>
/// Territory no-param constructor
/// </summary>
Territory::Territory(): id(-1), ownedBy(-1), continentId(-1), numberOfArmies(0), country(""){ }

/// <summary>
/// Constructor that sets the territory name, id, continent id
/// </summary>
/// <param name="country">the name of the country/territory</param>
/// <param name="id">the territory's id</param>
/// <param name="continentId">the id of the continent the territory belongs to</param>
Territory::Territory(std::string country, int id, int continentId): id(id), continentId(continentId), country(country), numberOfArmies(0), ownedBy(-1) { }

/// <summary>
/// Destructor 
/// </summary>
Territory::~Territory() {};

/// <summary>
/// Copy Contructor 
/// </summary>
/// <param name="territory"></param>
Territory::Territory(const Territory& territory): id(territory.id), continentId(territory.continentId), numberOfArmies(0), country(territory.country) {
	this->adjacentTerritoriesFrom = territory.adjacentTerritoriesFrom;
	this->adjacentTerritoriesTo = territory.adjacentTerritoriesTo;
}

void Territory::setOwner(int id) {
	ownedBy = id;
}

/// <summary>
/// Adds armies to the territory
/// </summary>
/// <param name="armies"></param>
void Territory::addArmies(int armies) {
	numberOfArmies += armies;
}

/// <summary>
/// Removes armies from the territory
/// In the case that there are too many armies removed and the number of armies left 
/// on the territory is negative, then we set the armies to 0
/// </summary>
/// <param name="armies"></param>
void Territory::removeArmies(int armies) {
	numberOfArmies -= armies;
	numberOfArmies = numberOfArmies > 0 ? numberOfArmies : 0;
}

/// <summary>
/// Overload of the assignment operator
/// /// </summary>
/// <param name="territory"></param>
/// <returns></returns>
Territory& Territory::operator= (const Territory& territory) {
	id = territory.id;
	country = territory.country;
	continentId = territory.continentId;
	numberOfArmies = territory.numberOfArmies;
	ownedBy = territory.ownedBy;
	adjacentTerritoriesFrom = territory.adjacentTerritoriesFrom;
	adjacentTerritoriesTo = territory.adjacentTerritoriesTo;

	return *this;
}

/// <summary>
/// This formats how the territory will be outputted when using cout << territory
/// </summary>
/// <param name="output"></param>
/// <param name="territory"></param>
/// <returns></returns>
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


// *********************************************************** MAP ***********************************************************

/// <summary>
/// Map no-param constructor
/// </summary>
Map::Map() { 
	this->territories = std::map<int, Territory*>();
	this->continents = std::map<int, Continent*>();
	this->continentTerritories = std::map<int, std::vector<Territory*>>();
}

/// <summary>
/// The maps copy constructor
/// </summary>
/// <param name="map"></param>
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

/// <summary>
/// The maps destructor, deletes all the pointers and sets the pointer to point to NULL
/// </summary>
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

std::map<int, std::vector<Territory*>> Map::getContinentTerritories() {
	return continentTerritories;
}

std::map<int, Continent*> Map::getContinents() {
	return continents;
}

/// <summary>
/// Overload of the assignment operator
/// </summary>
/// <param name="map"></param>
/// <returns></returns>
Map& Map::operator= (const Map& map) {
	this->territories = map.territories;
	this->continents = map.continents;
	this->continentTerritories = map.continentTerritories;
	return *this;
}

/// <summary>
/// This formats how the map will be outputted when using cout << map
/// </summary>
/// <param name="output">the output stream</param>
/// <param name="map">The mapo we are outputting</param>
/// <returns></returns>
std::ostream& operator << (std::ostream& output, const Map& map) {

	for (std::pair<int, std::vector<Territory*>> continent : map.continentTerritories) {
			output << "Continent: " << map.continents.at(continent.first)->name << std::endl;
		for (Territory* territory : continent.second) {
			output << *territory;
		}
	}

	return output;
}

/// <summary>
/// Returns the territory with the given id
/// </summary>
/// <param name="id">the id of the territory</param>
/// <returns></returns>
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
	if (id > 100) {
		std::cout << "something" << std::endl;
	}
	continentTerritories[continentId].push_back(territory);
	return territory;
}

/// <summary>
/// Creates a new continent and stores the continent information in the Map
/// </summary>
/// <param name="continent">the name of the continent</param>
/// <param name="continentId">the continent's id</param>
/// <param name="numberOfArmies">the bonus number of armies you get for conquering the entire continent</param>
/// <returns></returns>
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
	std::queue<Territory*> queue = std::queue<Territory*>();
	if (territories.size() < 1) {
		return false;
	}
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