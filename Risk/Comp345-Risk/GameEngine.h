#pragma once
#include "Map.h"
#include "MapLoader.h"
#include "Cards.h"
#include "Player.h"
#include <vector>



class StatsObserver;

using namespace std;

int main();

extern std::vector<Player*> players;
extern std::vector<int> playerorder;
extern Deck* deck;

class GameEngine {
public:

    int selectedMap;
    Map* map;
    MapLoader* mapLoader;
    int numOfPlayers;
    bool validMap;
    StatsObserver* statsObserver;

    Cards* card = new Cards();

    GameEngine();

    void setUp();
    void mainGameLoop();
    void removePlayersWithoutTerritories();
    void reinforcementPhase();
    void issueOrderPhase();
    void ordersExecutionPhase();
    bool hasWinner();
    void startUpPhase();
};

