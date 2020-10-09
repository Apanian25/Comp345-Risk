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
	Territory* t1 = map->addTerritory(1, 0, "test1", "Canada");
	Territory* t2 = map->addTerritory(2, 0, "test2", "Canada");
	Territory* t3 = map->addTerritory(3, 0, "test3", "Canada");
	Territory* t4 = map->addTerritory(4, 0, "test4", "Canada");
	Territory* t5 = map->addTerritory(5, 0, "test5", "Canada");
	//Territory* t6 = map->addTerritory(6, 0, "test6", "Canada");

	std::vector<int> connections = { 4, 5 };

	map->addEdge(1, 2);
	map->addEdge(2, 3);
	map->addEdges(3, connections);
	map->addEdge(4, 1);

	bool valid =  map->validate();

	delete map;
	return valid ? "Map is valid" : "Map is invalid";
}

std::string test2() {
	Map* map = new Map();
	Territory* t1 = map->addTerritory(1, 0, "test1", "Canada");
	Territory* t2 = map->addTerritory(2, 0, "test2", "Canada");
	Territory* t3 = map->addTerritory(3, 0, "test3", "Canada");
	Territory* t4 = map->addTerritory(4, 0, "test4", "Canada");
	Territory* t5 = map->addTerritory(5, 0, "test5", "Canada");
	Territory* t6 = map->addTerritory(6, 0, "test6", "Canada");

	std::vector<int> connections = { 4, 5 };

	map->addEdge(1, 2);
	map->addEdge(2, 3);
	map->addEdges(3, connections);
	map->addEdge(4, 1);

	bool valid = map->validate();

	delete map;
	return valid ? "Map is valid" : "Map is invalid";
}