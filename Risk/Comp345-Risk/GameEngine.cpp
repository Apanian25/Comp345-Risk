#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include "GameEngine.h"
#include <iostream>

Map* verifyMap(string mapPath);

int main() {

	int selectedMap;
	int numOfPlayers;
	bool observerOn{ false };
	bool validMap{ false };
	std::string path = "Maps";
	std::string Maps[7]{ 
		"artic.map", "canada.map",
		"europe.map", "solar.map",
		"sw_baltic.map", "invalidMapTest.map",
		"invalidSolarDisconnected.map" };

	std::cout << "GameEngine Driver Starting...\n" << std::endl;
	
	Map* map = NULL;

	while (map == NULL && !validMap) {

		std::cout << "Please select a map by entering its number from the following list:\n" << std::endl;

		for (size_t i = 0; i < 7; i++)
		{
			std::cout << i << ": " << Maps[i] << std::endl;
		}

		std::cin >> selectedMap;
		std::cout << "You've selected map number " << selectedMap << "." << endl;
		std::cout << "Verifying validity of map file..." << endl;

		MapLoader m;
		map = m.loadMap("Maps\\" + Maps[selectedMap]);

		//map = verifyMap();

		if (map != NULL) {
			cout << "Map file is valid. Verifying if it is a connected graph..." << endl;
			validMap = map->validate();
		}
	}


	cout << "yay valid map" << endl;

	

	


}

Map* verifyMap(string mapPath) {
	MapLoader m;
	Map* map;
	map = m.loadMap(mapPath);

	return map;
}