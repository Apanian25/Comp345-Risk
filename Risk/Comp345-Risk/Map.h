#pragma once
#include <vector>
#include <map>
#include <iostream>


namespace MapDriver {
	int main();
}

struct Territory {
	Territory();
	~Territory();
	Territory(std::string country, int id, int continent_id);
	Territory(const Territory& territory);
	Territory& operator= (const Territory& territory);

	std::string country;
	int continentId;
	int id;
	int ownedBy;
	std::vector<Territory*> adjacentTerritoriesTo;
	std::vector<Territory*> adjacentTerritoriesFrom;
};

struct Continent {
	Continent();
	~Continent();
	Continent(std::string name, int id, int numberOfArmies);
	Continent(const Continent& continent);
	Continent& operator= (const Continent& continent);

	int id;
	int numberOfArmies;
	std::string name;
};


class Map {
	private:
		std::map<int, Territory*> territories;
		std::map<int, Continent*> continents;
		std::map<int, std::vector<Territory*>> continentTerritories;

	public:
		Map();
		~Map();
		Map(const Map& map);
		Map& operator= (const Map& map);

		Continent* addContinent(std::string continent, int continentId, int numberOfArmies);
		Territory* addTerritory(std::string country, int id, int continentId);
		void addEdges(int src, std::vector<int> dest);
		void addEdge(int src, int dest);
		Territory* getTerritory(int id);
		bool validate();
};