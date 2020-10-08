#pragma once
#include <vector>
#include <map>
#include <iostream>


namespace MapDriver {
	int main();
}

struct Territory {
	std::string territory;
	std::string continent;
	int id;
	int numberOfArmies;
	int ownedBy;
	std::vector<Territory*> adjacentTerritoriesTo;
	std::vector<Territory*> adjacentTerritoriesFrom;
};


class Map {
	private:
		int size;
		std::map<int, Territory*> territories;

	public:
		Map();
		~Map();
		Territory* addTerritory(int id, int numberOfArmies, std::string name, std::string continent);
		void addEdges(int src, int dest[]);
		void addEdge(int src, int dest);
		Territory* getTerritory(int id);
		bool validate();
};