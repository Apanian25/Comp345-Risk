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
extern std::vector<Player*> players;
extern Deck* deck;

class GameEngine {
public:
	int selectedMap;
	Map* map = NULL;
	MapLoader m;
	int numOfPlayers{ 0 };

	Cards* card = new Cards();

	GameEngine();

	int mainGameLoop();
	void removePlayersWithoutTerritories();
	void reinforcementPhase();
	void issueOrderPhase(vector<Order*>& deploy, vector<Order*>& otherOrders);
	void ordersExecutionPhase(vector<Order*>& deploy, vector<Order*>& otherOrders);
	bool hasWinner();
};


