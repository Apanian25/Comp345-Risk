#include "MapLoader.h"
#include "Map.h"
using namespace std;

/// <summary>
/// Default Constructor
/// </summary>
MapLoader::MapLoader() {
	mapName = "";
	parsedMap = new Map();
}

/// <summary>
/// Sets the mapName
/// </summary>
/// <param name="mapName">MapName</param>
MapLoader::MapLoader(std::string mapName) {
	this->mapName = mapName;
	parsedMap = new Map();
}

/// <summary>
/// Destructor
/// </summary>
MapLoader::~MapLoader() {
	//call delete on map pointer created
	if(parsedMap != NULL)
		delete parsedMap;
	parsedMap = NULL;
}

/// <summary>
/// Overloading the stream insertion operator
/// </summary>
/// <param name="in"></param>
/// <param name="m"></param>
/// <returns></returns>
ostream & operator << (ostream& output, MapLoader& m)
{
	output << "The map name is ..." << m.mapName << endl;
	return output;
}


/// <summary>
/// Copy Constructor
/// </summary>
/// <param name="map">Map pointer</param>
MapLoader::MapLoader(const MapLoader &map){

	cout << "Copy constructor is being called...\n" << endl;
	this->mapName = map.mapName;
	this->parsedMap = map.parsedMap;
}

/// <summary>
/// Overloading Assignment Operator
/// </summary>
/// <param name="mapLoader"></param>
/// <returns></returns>
MapLoader& MapLoader::operator=(const MapLoader& mapLoader)
{
	//check for self-assignment
	if (this == &mapLoader)
		return *this;

	//copying
	mapName = mapLoader.mapName;

	return *this;
}

/// <summary>
/// Loads parsed map
/// </summary>
/// <param name="mapFilePath">path to the map file.</param>
/// <returns></returns>
Map* MapLoader::loadMap(std::string mapFilePath) {

	cout << "Verifying map before loading...\n" << endl; 

	parsedMap = readMap(mapFilePath);

	if (parsedMap == NULL) {
		cout << "Map was NOT successfully generated\n" << endl;
	}
	else {
		cout << "Map successfully generated, returning parsed map...\n" << endl;
	}

	return parsedMap;
}


/// <summary>
/// Reads and verifies map file while parsing it bit by bit.
/// </summary>
/// <param name="mapFilePath">Path to the map file.</param>
/// <returns>pointer to valid map, or NULL if map is invalid</returns>
Map* MapLoader::readMap(std::string mapFilePath) {

	std::string line{ "" };
	std::ifstream openFile(mapFilePath);

	if (!openFile.is_open()) {
		cout << "Unable to open the file selected. Please choose a valid text file.\n" << endl;
		return NULL;
	}

	if (openFile.peek() == std::ifstream::traits_type::eof()) {
		cout << "The file selected is empty. Please choose a different file.\n" << endl;
		return NULL;
	}

	cout << "Parsing map file...\n" << endl;
	if (openFile.is_open()) {
		while (getline(openFile, line)) {
			if (line.find("[continents]") == 0) {

				cout << "Found the continent section...\n" << endl;
				int continentId = 0;
				while (getline(openFile, line)) {
					if (line.length() != 0) {
						std::string info = line;
						std::vector<string> words = MapLoader::split(line, " ");

						if (words.size() != NUM_ENTRIES_CONTINENT) {
							cout << "The file has invalid continent information.\n" << endl;
							return NULL;
						}

						int numberOfArmies = std::stoi(words[1]);

						//Adding continent to map object, 0 is the string
						parsedMap->addContinent(words[0], ++continentId, numberOfArmies);

						cout << "Adding continent number " << continentId << "\n" << endl;
						cout << "Continent name: " << words[0] << "\n" << endl;
						cout << "Number of bonus armies: " << numberOfArmies << "\n" << endl;
					} 
					else {
						cout << "Finished adding continents.\n" << endl;
						break;
					}
				} 
			}


			if (line.find("[countries]") == 0) {
				cout << "Found the countries section...\n" << endl;
				while (getline(openFile, line)) {
					if (line.length() != 0) {
						std::string info = line;
						std::vector<string> words = MapLoader::split(line, " ");

						if (words.size() < NUM_ENTRIES_TERRITORIES) {
							cout << "The file has invalid territory information.\n" << endl;
							exit(1);
						}

						int territoryId = std::stoi(words[0]);
						int continentId = std::stoi(words[2]);

						//Adding territory to map object, 
						//0 is the territory id, 
						//1 is the name, 
						//2 is the country it belongs to (must match country id generated by map)
						parsedMap->addTerritory(words[1], territoryId, continentId);

						cout << "Adding country number " << territoryId << "\n" << endl;
						cout << "Country name: " << words[1] << "\n" << endl;
						cout << "Country belongs to continent number " << continentId << "\n" << endl;
					}
					else {
						cout << "Finished adding countries.\n" << endl;
						break;
					}
				}
			}


			if (line.find("[borders]") == 0) {
				cout << "Found the borders section...\n" << endl;
				while (getline(openFile, line)) {
					if (line.length() != 0) {
						std::string info = line;
						std::vector<string> words = MapLoader::split(line, " ");

						std::vector<int> borders;
						int countryId = std::stoi(words[0]);

						for (int i = 1; i < words.size(); ++i) {  

							borders.push_back(std::stoi(words[i]));
						}

						//Adding borders to map object
						parsedMap->addEdges(countryId, borders);

						cout << "Adding borders to country number " << countryId << "\n" << endl;
					}
					else {
						cout << "Finished adding borders.\n" << endl;
						break;
					}
				}
			}
			
		}
	}

	openFile.close();
	return parsedMap;
}

/// <summary>
/// Method to split the string line and returns it as vector of words
/// </summary>
/// <param name="s">the string need to be split</param>
/// <param name="delim">the delimeter between the words</param>
/// <returns>returns a vector of string words.</returns>
std::vector<string> MapLoader::split(string s, string delim) {

	vector<string> words;

	size_t pos = 0;
	std::string token;

	while ((pos = s.find(delim)) != std::string::npos) {

		token = s.substr(0, pos);
		if (token != "")
			words.push_back(token);
		s.erase(0, pos + delim.length());
	}

	//temporary hack until I figure out how to enter the last word
	if (!s.empty()) {
		words.push_back(s);
	}
	
	return words;
}
