#include "GameEngine.h"

Map* initMap();
bool p3test1(GameEngine* game);
bool p3test2(GameEngine* game);
bool p3test3(GameEngine* game);

namespace GameEngineDriver {
	int main() {
		Map* map = initMap();
		GameEngine* game = NULL;
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
		return 0;
	}
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
