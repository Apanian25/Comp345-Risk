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
static std::vector<Player*> players;

class gameEngine {
public:
	int selectedMap;
	Map* map = NULL;
	MapLoader m;
	int numOfPlayers{ 0 };

	Cards* card = new Cards();
	Deck* deck = new Deck();

	gameEngine();
};


