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

class gameEngine {
public:
	int selectedMap;
	Map* map = NULL;
	MapLoader m;
	int numOfPlayers{ 0 };

	std::vector<Player*> players;
	Cards* card = new Cards();
	Deck* deck = new Deck();

	gameEngine();
};
