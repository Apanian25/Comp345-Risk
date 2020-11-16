#include "GameEngine.h"
#include "Cards.h"
#include "Map.h"
#include "Player.h"
#include <vector>
#include <map>
#include <iostream>

GameEngine::GameEngine()
{

};

extern Deck* deck = new Deck();
extern vector<Player*> players = vector<Player*>();

bool observerOn{ 0 };

int main() {
	GameEngine* engine = new GameEngine();

		int selectedMap;
		Map* map = NULL;
		MapLoader* m = NULL;
		int numOfPlayers{ 0 };

		bool validMap{ false };

		vector<Player*> players;
		Cards* card = new Cards();
		Deck* deck = new Deck();

		string path = "Maps";
		string Maps[7]{
			"artic.map", "canada.map",
			"europe.map", "solar.map",
			"sw_baltic.map", "invalidMapTest.map",
			"invalidSolarDisconnected.map" };

		cout << "--- GameEngine Driver Starting... ---\n" << std::endl;

		while (map == NULL || !validMap) {
	while (engine->map == NULL && !validMap) {

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

				if (m != NULL) {
					delete m;
					m = NULL;
				}

				m = new MapLoader();

				map = m->loadMap("Maps\\" + Maps[selectedMap]);

				if (map != NULL) {
					cout << "--- Map file exists. Verifying if it is a connected graph... ---" << endl;
					validMap = map->validate();
				}

				if (!validMap) {
					cout << "--- Map is not a connectd graph. Please choose another map... ---" << endl;
				}
			}
		}
		if (engine->map != NULL) {
			cout << "--- Map file is valid. Verifying if it is a connected graph... ---" << endl;
			validMap = engine->map->validate();
		}
	}

	cout << "--- Congratulations, the map is valid! ---" << endl;

	while (engine->numOfPlayers < 2 || engine->numOfPlayers >5) {

		cout << "Please enter the number of players (2-5): " << endl;
		cin >> engine->numOfPlayers;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(512, '\n');
			cout << "You did not enter a valid integer." << endl;
		}

		if (engine->numOfPlayers < 2 || engine->numOfPlayers > 5) {
			cout << "Invalid number of players. Please try a number between 2 and 5." << endl;
		}
	}

		for (size_t i = 0; i < numOfPlayers; i++)
		{
			string playerName{ "Player " + std::to_string(i) };
			Player* player = new Player(playerName);
			players.push_back(player);
		}
	for (size_t i = 0; i < engine->numOfPlayers; i++)
	{
		std::string playerName{ "Player " + std::to_string(i) };
		Player* player = new Player(i, playerName);
		players.push_back(player);
	}

	cout << "You have chosen " << engine->numOfPlayers << " players." << endl;

	for (size_t i = 0; i < players.size(); i++)
	{
		cout << "The players are: " << endl;
		cout << players[i] << endl;
	}

	cout << "--- Initializing deck ---" << endl;
	deck->initialize(*deck, *engine->card);
	cout << deck << endl;
	cout << "--- Shuffling deck ---" << endl;
	deck->shuffle(*deck);
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

	return 0;
}


//*********************************************************  PART3  *********************************************************
void GameEngine::mainGameLoop() {
	do {
		removePlayersWithoutTerritories();
		reinforcementPhase();
		issueOrderPhase();
		ordersExecutionPhase();

		for (Player* player : players) {
			player->hasConqueredTerritory = false;
			//player->hasNegotiatedWithID = -500;
		}
	} while (hasWinner());
}

void GameEngine::removePlayersWithoutTerritories() {
	vector<Player*> playersToRemove;
	for (Player* player : players) {
		if (player->getTerritories().size() == 0) {
			playersToRemove.push_back(player);
		}
	}

	for (Player* player : playersToRemove) {
		players.erase(std::remove(players.begin(), players.end(), player));
	}
}

void GameEngine::issueOrderPhase() {
	for (Player* player : players) {
		while (true) {
			Order* order = player->issueOrder();
			if (order == NULL)
				break;
		}
	}
}

void GameEngine::reinforcementPhase() {
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
			delete order;
			player->orders.erase(std::remove(player->orders.begin(), player->orders.end(), order));
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
	int point = territories.at(0)->ownedBy;
	for (pair<int, Territory*> territory : territories) {
		if (territory.second->ownedBy != point)
			return false;
	}

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