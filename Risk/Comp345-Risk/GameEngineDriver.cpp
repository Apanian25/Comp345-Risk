#include "GameEngine.h"

Map* initMap();
bool p3test1(GameEngine* game);
bool p3test2(GameEngine* game);
bool p3test3(GameEngine* game);
bool a3p2test1();
bool a3p1test(GameEngine* game);

void testInvalid(MapLoader* loader);
void testValid(MapLoader* loader);

/// <summary>
/// Tests the functionality of Assignment 2
/// </summary>
/// <param name="game"></param>
void testA2(GameEngine* game) {
	Map* map = initMap();
	if (map != NULL) {
		game = new GameEngine();
		game->map = map;
		cout << "Test1 valid: " << p3test1(game) << endl << endl;
		cout << "Test3 valid: " << p3test3(game) << endl << endl;
		delete game->map;
		for (Player* p : players) {
			delete p;
			p = NULL;
		}
		players.clear();
		cout << "Test2 valid: " << p3test2(game) << endl << endl;
	}

	if (map != NULL && game != NULL) {
		delete game;
		game = NULL;
	}
}


namespace GameEngineDriver {
	int main() {
		GameEngine* game = new GameEngine();

		//testA2(game);
		//we call this twice so that the user can test both types of readers
		a3p2test1();
		a3p2test1();
		a3p1test(game);
		

		delete game;
		return 0;
	}
}

/// <summary>
/// initialize a rando m map to test with
/// </summary>
/// <returns></returns>
Map* initMap() {
	Map* map = new Map();
	map->addContinent("Canada", 2, 20);

	Territory* t1 = map->addTerritory("Quebec", 1, 2);
	Territory* t2 = map->addTerritory("Ontario", 2, 2);
	Territory* t3 = map->addTerritory("British Columbia", 3, 2);
	Territory* t4 = map->addTerritory("Nova Scotia", 4, 2);
	Territory* t5 = map->addTerritory("Alberta", 5, 2);

	std::vector<int> connections = { 4, 5 };

	map->addEdge(1, 2);
	map->addEdge(2, 3);
	map->addEdges(3, connections);
	map->addEdge(4, 1);

	bool valid = map->validate();

	if (valid)
		return map;

	delete map;
	map = NULL;

	return NULL;
}

/// <summary>
/// a player receives the correct number of armies in the reinforcement phase(showing different cases);
/// </summary>
/// <returns></returns>
bool p3test1(GameEngine* game) {
	Player* player = new Player(1, "Nicholas", new NeutralPlayerStrategy());
	players.push_back(player);
	for (std::pair<int,Territory*> terr : game->map->getAllTerritories()) {
		player->territories.push_back(terr.second);
		terr.second->ownedBy = player->id;
	}
	game->reinforcementPhase();

	bool isValid = player->numOfArmies == 23;
	return isValid;
}

/// <summary>
///  a player will only issue deploy orders and no other kind of orders if they still have armies in their reinforcement pool;
/// the game engine will only execute non-deploy orders when all the deploy orders of all players have been executed;
/// a player can issue advance orders to either defend or attack, based on the toAttack() and toDefend() lists;
/// a player can play cards to issue orders;
/// a player that does not control any territory is removed from the game;
/// during the game execution we can also observe all the other parts, and what they are supposed to do
/// </summary>
/// <returns></returns>
bool p3test2(GameEngine* game) {
	//Better to demonstrate this part via a run of the game
	game->setUp();
	return true;
}


/// <summary>
/// the game ends when a single player controls all the territories
/// </summary>
/// <returns></returns>
bool p3test3(GameEngine* game) {
	game->mainGameLoop();
	return true;
}


/// <summary>
/// Tests the functionality of Assignment 3 part 2
/// </summary>
/// <returns></returns>
bool a3p2test1()
{
	int choice{ 0 };

	std::cout << "Please select if you want to use Domination MapLoader (press 0), or if you want to use Conquest FileReader (press 1) " << std::endl;

	std::cin >> choice;
	std::cout << std::endl;

	if (choice == 0) {

		std::cout << "MapLoaderDriver\n" << std::endl;
		std::cout << "Loading Domination Map" << std::endl;

		MapLoader* loader = new MapLoader("solar");

		Map* map = loader->loadMap("Maps\\solar.map");

		std::cout << "Successfully loaded domination map: \"solar.map\"" << std::endl;

		//deleting loader is enough, map gets deleted inside the destructor in mapLoader.
		delete loader;
		loader = NULL;

	}

	else if (choice == 1) {

		std::cout << "Using the ConquestFileReader....\n" << std::endl;
		std::cout << "Loading Conquest Map" << std::endl;

		ConquestFileReader* loader = new ConquestFileReader("ConquestWorld");
		ConquestFileReaderAdapter* adapter = new ConquestFileReaderAdapter(loader);
		Map* map = adapter->loadMap("Maps\\ConquestWorld.map");

		std::cout << "Successfully loaded conquest map: \"ConquestWorld.map\"" << std::endl;

		//map gets deleted inside of loader which gets delete inside of adapter, so do not need to explicitly delete them here
		if (adapter != nullptr) {
			delete adapter;
			adapter = nullptr;
		}
	}

	return 0;
}

bool a3p1test(GameEngine* game)
{
	cout << "Testing the Different strategies for the different players playing the game" << endl;
	game->setUp();
	return true;
}
