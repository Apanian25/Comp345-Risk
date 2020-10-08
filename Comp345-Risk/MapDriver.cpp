#include "Map.h"
#include <iostream>


bool test1();

namespace MapDriver {
	int main() {
		std::cout << "MapDriver" << std::endl;
		std::cout << "test1: Testing Connected Map" << std::endl;
		std::cout << "test1: Results: " << test1() << std::endl;

		return 1;
	}
}


bool test1() {
	Map* map = new Map();
	Territory* t1 = map->addTerritory(1, 0, "test1", "Canada");
	Territory* t2 = map->addTerritory(2, 0, "test2", "Canada");
	Territory* t3 = map->addTerritory(3, 0, "test3", "Canada");
	Territory* t4 = map->addTerritory(4, 0, "test4", "Canada");
	Territory* t5 = map->addTerritory(5, 0, "test5", "Canada");
	Territory* t6 = map->addTerritory(6, 0, "test6", "Canada");

	int connections[]{ 4,5 };

	map->addEdge(1, 2);
	map->addEdge(2, 3);
	map->addEdges(3, connections);
	map->addEdge(4, 1);

	return map->validate();
}


