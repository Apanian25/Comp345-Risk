#include "GameEngine.h"
#include <stdlib.h>
#include <iostream>
#include <time.h>


bool observerOn{ 0 };

int main() {
	gameEngine* engine = new gameEngine();

	bool validMap{ false };
	std::string path = "Maps";
	std::string Maps[7]{
		"artic.map", "canada.map",
		"europe.map", "solar.map",
		"sw_baltic.map", "invalidMapTest.map",
		"invalidSolarDisconnected.map" };

	std::cout << "--- GameEngine Driver Starting... ---\n" << std::endl;

	while (engine->map == NULL && !validMap) {

		std::cout << "Please select a map by entering its number from the following list:\n" << std::endl;

		for (size_t i = 0; i < 7; i++)
		{
			std::cout << i << ": " << Maps[i] << std::endl;
		}

		std::cin >> engine->selectedMap;
		std::cout << "--- You've selected map number " << engine->selectedMap << ". ---" << endl;
		std::cout << "--- Verifying validity of map file... ---" << endl;

		engine->map = engine->m.loadMap("Maps\\" + Maps[engine->selectedMap]);

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
	playerorder= startupPhase(players, engine->map);
	return 0;
}

/// <summary>
/// Method to turn the observers on/off during the game start phase
/// </summary>


std::vector<int> startupPhase(std::vector<Player*> players, Map* map) {
	cout << "The order of the players are as follows: " << endl;

	std::vector<int> playerrandom;
	std::vector<int> playerorder;
	for (int i = 0; i < players.size(); i++) {
		playerrandom.push_back(i);
	}
	int randoms;
	srand(time(NULL));
	while (playerrandom.size() != 0) {
		randoms = rand() % playerrandom.size();
		playerorder.push_back(playerrandom.at(randoms));
		playerrandom.erase(playerrandom.begin() + randoms);
	}
	for (int i = 0; i < players.size(); i++) {
		cout << playerorder.at(i) << " ";
	}
	cout << endl;
	std::vector<int> terrsize;

	for (int i = 1; i <= map->getSize(); i++) {
		terrsize.push_back(i);

	}
	int ind = 0;
	while (terrsize.size() != 0) {
		randoms = rand() % terrsize.size();
		players.at(playerorder.at(ind % players.size()))->addTerritory(map->getTerritory(terrsize.at(randoms)));
		map->getTerritory(terrsize.at(randoms))->ownedBy = ind % players.size();
		terrsize.erase(terrsize.begin() + randoms);
		ind++;
	}
	

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
	return playerorder;
}
void turnObserversOnOff() {
	if (observerOn) {
		observerOn = 0;
	}
	else {
		observerOn = 1;
	}
}