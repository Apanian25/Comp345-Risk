#pragma once
#include "Map.h"
#include "MapLoader.h"
#include "Cards.h"
#include "Player.h"
#include <vector>
#include <iostream>
using namespace std;


class StatsObserver;

using namespace std;

namespace GameEngineDriver {
    int main();
}

extern std::vector<Player*> players;
extern std::vector<int> playerorder;
extern Deck* deck;

class GameEngine {
public:

    int selectedMap;
    Map* map;
    MapLoader* mapLoader;
    int numOfPlayers;
    StatsObserver* statsObserver;

    GameEngine();
    ~GameEngine();


    GameEngine(const GameEngine& engine);
    friend ostream& operator << (ostream& out, const GameEngine& engine);
    GameEngine& operator = (const GameEngine& engine);

    void setUp();
    void mainGameLoop();
    void removePlayersWithoutTerritories();
    void reinforcementPhase();
    void issueOrderPhase();
    void ordersExecutionPhase();
    bool hasWinner();
    void startUpPhase();
};

