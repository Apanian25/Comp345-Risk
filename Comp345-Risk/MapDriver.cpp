#include "Map.h"
#include <iostream>

std::string test1();
std::string test2();

namespace MapDriver {
	int main() {
		std::cout << "MapDriver" << std::endl;
		std::cout << "test1: Testing Connected Map" << std::endl;
		std::cout << "test1: Results: " << test1() << std::endl;
		std::cout << "test2: Testing NON-Connected Map" << std::endl;
		std::cout << "test2: Results: " << test2() << std::endl;

		return 1;
	}
}


std::string test1() {
	Map* map = new Map();
	map->addContinent("Canada", 2, 20);

	Territory* t1 = map->addTerritory("Quebec", 1, 2);
	Territory* t2 = map->addTerritory("Ontario", 2, 2);
	Territory* t3 = map->addTerritory("British Columbia", 3, 2);
	Territory* t4 = map->addTerritory("Nova Scotia", 4, 2);
	Territory* t5 = map->addTerritory("Alberta", 5, 2);
	//Territory* t6 = map->addTerritory(6, 0, "test6", "Canada");

	std::vector<int> connections = { 4, 5 };

	map->addEdge(1, 2);
	map->addEdge(2, 3);
	map->addEdges(3, connections);
	map->addEdge(4, 1);

	bool valid =  map->validate();

	std::cout << *map;
	delete map;
	map = NULL;
	return valid ? "Map is valid" : "Map is invalid";
}

std::string test2() {
	Map* map = new Map();
	Territory* t1 = map->addTerritory("test1", 1, 2);
	Territory* t2 = map->addTerritory("test2", 2, 2);
	Territory* t3 = map->addTerritory("test3", 3, 2);
	Territory* t4 = map->addTerritory("test4", 4, 2);
	Territory* t5 = map->addTerritory("test5", 5, 2);
	Territory* t6 = map->addTerritory("test6", 6, 2);

	std::vector<int> connections = { 4, 5 };

	map->addEdge(1, 2);
	map->addEdge(2, 3);
	map->addEdges(3, connections);
	map->addEdge(4, 1);

	bool valid = map->validate();

	delete map;
	map = NULL;
	return valid ? "Map is valid" : "Map is invalid";
}