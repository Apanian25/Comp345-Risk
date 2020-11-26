#pragma once
#include <vector>
#include <map>
#include <iostream>


namespace MapDriver {
	int main();
}

struct Continent {
	Continent();
	~Continent();
	Continent(std::string name, int id, int numberOfArmies);
	Continent(const Continent& continent);
	Continent& operator= (const Continent& continent);
	friend std::ostream& operator << (std::ostream& output, const Continent& continent);


	int id;
	int numberOfArmies;
	std::string name;
};

struct Territory {
	Territory();
	~Territory();
	Territory(std::string country, int id, int continent_id);
	Territory(const Territory& territory);
	void addArmies(int armies);
	void removeArmies(int armies);
	void setOwner(int id);
	Territory& operator= (const Territory& territory);
	friend std::ostream & operator << (std::ostream& output, const Territory& territory);



	std::string country;
	int continentId;
	int id;
	int numberOfArmies;
	int commitedNumberOfArmies;
	int ownedBy;
	std::vector<Territory*> adjacentTerritoriesTo;
	std::vector<Territory*> adjacentTerritoriesFrom;
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
		friend std::ostream& operator << (std::ostream& output, const Map& map);

		Continent* addContinent(std::string continent, int continentId, int numberOfArmies);
		Territory* addTerritory(std::string country, int id, int continentId);
		void addEdges(int src, std::vector<int> dest);
		void addEdge(int src, int dest);
		Territory* getTerritory(int id);
		int getSize();
		std::map<int, Continent*> getContinents();
		std::map<int, std::vector<Territory*>> getContinentTerritories();
		std::map<int, Territory*> getAllTerritories();

		bool validate();
};