#pragma once
#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include <vector>

using namespace std;

int main();
void turnObserversOnOff();
std::vector<int> startupPhase(std::vector<Player*> players, Map* map);
extern std::vector<Player*> players;
extern std::vector<int> playerorder;
extern Deck* deck;

class gameEngine {
public:
	int selectedMap;
	Map* map = NULL;
	MapLoader m;
	int numOfPlayers{ 0 };
	

	Cards* card = new Cards();

	gameEngine();
};
