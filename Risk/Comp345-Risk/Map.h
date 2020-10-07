#pragma once

namespace Map {
	int main();
}

struct Territory {
	std::string territory;
	std::string continent;
	int id;
	int ownedBy;
	std::vector<Territory*> adjacentTerritoriesTo;
	std::vector<Territory*> adjacentTerritoriesFrom;
};

class Map {
	Map();
	~Map();
	Territory* addTerritory(int id, std::string name, std::string continent);
	void addEdges(int src, int dest[]);
	void addEdge(int src, int dest);
	Territory* getTerritory(int id);
	bool validate();
};