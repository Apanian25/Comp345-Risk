#include "GameEngine.h"

Map* initMap();
bool p3test1(GameEngine* game);
bool p3test2();
bool p3test3();
bool p3test4();
bool p3test5();
bool p3test6();
bool p3test7();


int testPart3() {
	Map* map = initMap();
	if (map != NULL) {
		GameEngine* game = new GameEngine();
		game->map = map;
		p3test1(game);
		p3test2();
		p3test3();
		p3test4();
		p3test5();
		p3test6();
		p3test7();
	}

	delete map;
	map = NULL;
	return 0;
}

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
	Player* player = new Player(1, "Nicholas");
	players.push_back(player);
	for (std::pair<int,Territory*> terr : game->map->getAllTerritories()) {
		player->territories.push_back(terr.second);
		terr.second->ownedBy = player->id;
	}
	game->reinforcementPhase();

	bool isValid = player->numOfArmies == 3;
	delete player;
	return isValid;
}

/// <summary>
///  a player will only issue deploy orders and no other kind of orders if they still have armies in their reinforcement pool;
/// </summary>
/// <returns></returns>
bool p3test2() {
	return false;
}

/// <summary>
///  the game engine will only execute non-deploy orders when all the deploy orders of all players have been executed;
/// </summary>
/// <returns></returns>
bool p3test3() {
	return false;
}

/// <summary>
///  a player can issue advance orders to either defend or attack, based on the toAttack() and toDefend() lists;
/// </summary>
/// <returns></returns>
bool p3test4() {
	return false;
}

/// <summary>
/// a player can play cards to issue orders;
/// </summary>
/// <returns></returns>
bool p3test5() {
	return false;
}

/// <summary>
/// a player that does not control any territory is removed from the game;
/// </summary>
/// <returns></returns>
bool p3test6() {
	return false;
}

/// <summary>
///  the game ends when a single player controls all the territories
/// </summary>
/// <returns></returns>
bool p3test7() {
	return false;
}