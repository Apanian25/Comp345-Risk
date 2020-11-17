#include "GameEngine.h"
#include "Cards.h"
#include "Map.h"
#include "Player.h"
#include <vector>
#include <map>
#include <iostream>

GameEngine::GameEngine()
{
	selectedMap = -1;
	map = NULL;
	mapLoader = NULL;
	numOfPlayers = 0;
	validMap = false;

};

extern Deck* deck = new Deck();
extern vector<Player*> players = vector<Player*>();
bool observerOn{ 0 };

//*********************************************************  PART1  *********************************************************

void GameEngine::setUp() {

	Cards* card = new Cards();
	Deck* deck = new Deck();
	deck->initialize();

	string path = "Maps";
	string Maps[7]{
		"artic.map", "canada.map",
		"europe.map", "solar.map",
		"sw_baltic.map", "invalidMapTest.map",
		"invalidSolarDisconnected.map" };

	cout << "--- GameEngine Driver Starting... ---\n" << std::endl;
		
	while (map == NULL || !validMap) {

		cout << "Please select a map by entering its number from the following list:\n" << std::endl;

		for (size_t i = 0; i < 7; i++)
		{
			cout << i << ": " << Maps[i] << std::endl;
		}
			
		cin >> selectedMap;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(512, '\n');
			cout << "You did not enter a valid integer." << endl;
			cout << "" << endl;
			selectedMap = -1;
		}

		if (selectedMap < 0 && selectedMap != -1 || selectedMap >6) {
			cout << " --- You've selected an invalid map number ---" << endl;
			cout << "" << endl;
		}

		if (selectedMap >= 0 && selectedMap < 7) {

			cout << "--- You've selected map number " << selectedMap << ". ---" << endl;
			cout << "--- Verifying validity of map file... ---" << endl;

			if (mapLoader != NULL) {
				delete mapLoader;
				mapLoader = NULL;
			}

			mapLoader = new MapLoader();

			map = mapLoader->loadMap("Maps\\" + Maps[selectedMap]);

			if (map != NULL) {
				cout << "--- Map file exists. Verifying if it is a connected graph... ---" << endl;
				validMap = map->validate();
			}

			if (!validMap) {
				cout << "--- Map is not a connectd graph. Please choose another map... ---" << endl;
			}
		}
	}
		
	cout << "--- Congratulations, the map is valid! ---" << endl;
		
	while (numOfPlayers < 2 || numOfPlayers >5) {
			
		cout << "Please enter the number of players (2-5): " << endl;
		cin >> numOfPlayers;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(512, '\n');
			cout << "You did not enter a valid integer." << endl;
		}

		if (numOfPlayers < 2 || numOfPlayers > 5) {
			cout << "Invalid number of players. Please try a number between 2 and 5." << endl;
		}
	}

	for (size_t i = 0; i < numOfPlayers; i++)
	{
		string playerName{ "Player " + to_string(i) };
		Player* player = new Player(i, playerName);
		players.push_back(player);
	}
		
	cout << "You have chosen " << numOfPlayers << " players." << endl;

	for (size_t i = 0; i < players.size(); i++)
	{
		cout << "The players are: " << endl;
		cout << players[i] << endl;
	}

	cout << "--- Initializing deck ---" << endl;
	deck->initialize();
	cout << deck << endl;
	cout << "--- Shuffling deck ---" << endl;
	deck->shuffle();
	cout << deck << endl;


	cout << "Please choose whether you'd like the observers to be On(1) or Off(0): " << endl;
	cin >> observerOn;

	while (cin.fail()) {
		cin.clear();
		cin.ignore(512, '\n');
		cout << "You did not enter a valid input. Setting the observers off." << endl;
	}

	if (observerOn) {
		cout << "The observers are now on." << endl;
	}
	else {
		cout << "The observers are off." << endl;
	}

	startUpPhase();
	mainGameLoop();
}

//*********************************************************  PART2  *********************************************************
void GameEngine::startUpPhase() {

	cout << "The order of the players are as follows: " << endl;

	std::vector<int> playerrandom;
	std::vector<int> playerorder;
	for (int i = 0; i < players.size(); i++) {
		playerrandom.push_back(i);
	}
	int randoms;
	srand(time(NULL));
	//randomize
	while (playerrandom.size() != 0) {
		randoms = rand() % playerrandom.size();
		playerorder.push_back(playerrandom.at(randoms));
		cout << playerrandom.at(randoms) << endl;
		playerrandom.erase(playerrandom.begin() + randoms);
	}

	
	std::vector<int> terrsize;

	for (int i = 1; i <= map->getSize(); i++) {
		terrsize.push_back(i);
	}

	int ind = 0;
	while (terrsize.size() != 0) {
		randoms = rand() % terrsize.size();
		Player* p = players.at(playerorder.at(ind % players.size()));
		p->addTerritory(map->getTerritory(terrsize.at(randoms)));
		map->getTerritory(terrsize.at(randoms))->ownedBy = p->id;
		terrsize.erase(terrsize.begin() + randoms);
		ind++;
	}

	for (size_t i = 0; i < players.size(); i++)
	{
		cout << "The players are: " << endl;
		cout << *players[i] << endl;
	}

	cout << players[0]->getNumOfArmies() << endl;
	int A;

	switch (players.size()) {
	case 2:
		A = 40;
		break;
	case 3:
		A = 35;
		break;
	case 4:
		A = 30;
		break;
	case 5:
		A = 25;
		break;
	}
	for (int i = 0; i < players.size(); i++) {
		players[i]->giveArmies(A);
	}

	vector<Player*> orderedPlayers;
	for (int i = 0; i < players.size(); ++i) {
		orderedPlayers.push_back(players.at(playerorder.at(i)));
	}
	players = orderedPlayers;

	cout << players[0]->getNumOfArmies() << endl;
}


//*********************************************************  PART3  *********************************************************
void GameEngine::mainGameLoop() {
	int round = 1;
	do {
		cout << "STARTING ROUND" << round << endl;
		removePlayersWithoutTerritories();
		reinforcementPhase();
		issueOrderPhase();
		ordersExecutionPhase();

		for (Player* player : players) {
			player->hasConqueredTerritory = false;
			player->hasNegotiatedWithId = -500;
		}
		for (pair<int, Territory*> territory : map->getAllTerritories()) {
			territory.second->commitedNumberOfArmies = 0;
		}
		++round;
	} while (!hasWinner());
	cout << "Game lasted " << --round << " rounds" << endl;
}

void GameEngine::removePlayersWithoutTerritories() {
	vector<Player*> playersToRemove;
	for (Player* player : players) {
		if (player->getTerritories().size() == 0) {
			playersToRemove.push_back(player);
		}
		while (player->hand->hand.size() > 0) {
			deck->cards_list.push_back(player->hand->hand.at(0));
			player->hand->hand.erase(std::remove(player->hand->hand.begin(), player->hand->hand.end(), player->hand->hand.at(0)));
		}
	}

	for (Player* player : playersToRemove) {
		players.erase(std::remove(players.begin(), players.end(), player));
	}
}

void GameEngine::issueOrderPhase() {
	cout << "Executing Issue Order Phase" << endl;
	for (Player* player : players) {
		while (true) {
			Order* order = player->issueOrder();
			if (order == NULL)
				break;
		}
	}
}

void GameEngine::reinforcementPhase() {
	cout << "Executing Reinforcement Phase" << endl;
	std::map<int, std::vector<Territory*>> continentTerritories = map->getContinentTerritories();
	std::map<int, Continent*> continents = map->getContinents();

	for (Player* player : players) {
		int numberOfTerritorys = player->getTerritories().size();
		int bonusArmies{ numberOfTerritorys <= 9 ? 3 : numberOfTerritorys / 3 };


		for (pair<int, std::vector<Territory*>> continent : continentTerritories) {
			bool ownsContinent = true;
			for (Territory* territory : continent.second) {
				if (territory->ownedBy != player->id) {
					ownsContinent = false;
					break;
				}
			}
			if (ownsContinent) {
				bonusArmies += continents[continent.first]->numberOfArmies;
			}
		}
		player->giveArmies(bonusArmies);
	}
}

void GameEngine::ordersExecutionPhase() {
	cout << "Executing Orders Phase" << endl;
	//Deploy orders execute first
	for (Player* player : players) {
		vector<Order*> deploys;
		for (Order* order : player->orders) {
			if (dynamic_cast<Deploy*>(order)) {
				deploys.push_back(order);
			}
		}

		for (Order* order : deploys) {
			order->execute();
			player->orders.erase(std::remove(player->orders.begin(), player->orders.end(), order));
			delete order;
		}
	}

	//Other orders execute second.
	for (Player* player : players) {
		for (Order* order : player->orders) {
			order->execute();
			delete order;
		}

		player->orders.clear();
		if (player->hasConqueredTerritory) {
			player->hand->draw(*deck);
		}
	}
}

bool GameEngine::hasWinner() {
	std::map<int, Territory*> territories = map->getAllTerritories();
	int point = territories.begin()->second->ownedBy;
	for (pair<int, Territory*> territory : territories) {
		if (territory.second->ownedBy != point)
			return false;
	}

	Player* winner = NULL;
	for (Player* player : players) {
		if (player->id == point)
			winner = player;
	}

	//winner will not be null
	cout << "WINNER: " << *winner << endl;
	return true;
}




/// <summary>
/// Method to turn the observers on/off during the game start phase
/// </summary>
void turnObserversOnOff() {
	if (observerOn) {
		observerOn = 0;
	}
	else {
		observerOn = 1;
	}
}