#include "GameEngine.h"
#include <iostream>


bool observerOn{ 0 };

	int main() {

		int selectedMap;
		Map* map = NULL;
		MapLoader m;
		int numOfPlayers{ 0 };

		bool validMap{ false };

		std::vector<Player*> players;
		Cards* card = new Cards();
		Deck* deck = new Deck();

		std::string path = "Maps";
		std::string Maps[7]{
			"artic.map", "canada.map",
			"europe.map", "solar.map",
			"sw_baltic.map", "invalidMapTest.map",
			"invalidSolarDisconnected.map" };

		std::cout << "--- GameEngine Driver Starting... ---\n" << std::endl;

		while (map == NULL && !validMap) {

			std::cout << "Please select a map by entering its number from the following list:\n" << std::endl;

			for (size_t i = 0; i < 7; i++)
			{
				std::cout << i << ": " << Maps[i] << std::endl;
			}

			std::cin >> selectedMap;
			std::cout << "--- You've selected map number " << selectedMap << ". ---" << endl;
			std::cout << "--- Verifying validity of map file... ---" << endl;

			map = m.loadMap("Maps\\" + Maps[selectedMap]);

			if (map != NULL) {
				cout << "--- Map file is valid. Verifying if it is a connected graph... ---" << endl;
				validMap = map->validate();
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
			std::string playerName{ "Player " + std::to_string(i) };
			Player* player = new Player(playerName);
			players.push_back(player);
		}

		cout << "You have chosen " << numOfPlayers << " players." << endl;

		for (size_t i = 0; i < players.size(); i++)
		{
			cout << "The players are: " << endl;
			cout << *players[i] << endl;
		}

		cout << "--- Initializing deck ---" << endl;
		deck->initialize(*deck, *card);
		cout << *deck << endl;
		cout << "--- Shuffling deck ---" << endl;
		deck->shuffle(*deck);
		cout << *deck << endl;


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