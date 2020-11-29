#include "MapLoader.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
namespace fs = std::experimental::filesystem;


void testValid(MapLoader* loader);
void testInvalid(MapLoader* loader);
namespace MapLoaderDriver {
	int main() {

		int choice{ 0 };

		std::cout << "Please select if you want to use MapLoader (press 0), or if you want to use FileReader (press 1) " << std::endl;

		std::cin >> choice;
		std::cout << std::endl;

		if (choice == 0) {

			std::cout << "MapLoaderDriver\n" << std::endl;

			MapLoader* loader = new MapLoader("solar");

			testValid(loader);
			testInvalid(loader);

			delete loader;
			loader = NULL;

		}

		else if (choice == 1) {

			std::cout << "Using the ConquestFileReader....\n"<<std::endl;

			ConquestFileReader* loader = new ConquestFileReader("World");
			ConquestFileReaderAdapter* adapter = new ConquestFileReaderAdapter(*loader);
			Map* map = adapter->loadMap("Maps\\Earth.map");
			cout << map->validate();
			//loader->readConquestMap("Maps\Africa.map");


		}


		return 0;


	}
}

void testValid(MapLoader* loader) {
	Map* map = loader->loadMap("Maps\\solar.map");
	if (map == NULL) {
		cout << "MAP is invalid, failed to load (should be valid) " << endl;
	}
	else {
		cout << "Map: " << loader->mapName << " was valid" << endl;
	}
	delete map;
	map = NULL;
}

void testInvalid(MapLoader* loader) {
	//invalid maps
	std::string path = "Maps";
	std::string invalidMaps[10]{ "NoBordersHeader.map", "NoBordersSolar.map",
								"NoContinentHeader.map", "NoContinentsSolar.map",
								"NoCountriesContinentID.map", "NoCountriesHeader.map",
								"NoCountriesID.map", "NoCountriesSolar.map",
								"NoHeaders.map", "NoNumOfArmies.map" };

	for (size_t i = 0; i < 10; i++)
	{
		Map* map = loader->loadMap(invalidMaps[i]);
		if (map == NULL) {
			cout << "MAP: " << invalidMaps[i] << " is invalid, failed to load" << endl;
		}
		else {
			cout << "MAP is valid(but it shouldn't be)" << endl;
		}
		delete map;
		map = NULL;
	}
}