#pragma once
#include "Map.h"
#include "MapLoader.h"
#include "Cards.h"
#include "Player.h"
#include <vector>


using namespace std;

int main();
void turnObserversOnOff();
extern std::vector<Player*> players;
extern Deck* deck;

class GameEngine {
public:
	int selectedMap;
	Map* map;
	MapLoader* mapLoader;
	int numOfPlayers;
	bool validMap;

	Cards* card = new Cards();

	GameEngine();

	void mainGameLoop();
	void removePlayersWithoutTerritories();
	void reinforcementPhase();
	void issueOrderPhase();
	void ordersExecutionPhase();
	bool hasWinner();
};


