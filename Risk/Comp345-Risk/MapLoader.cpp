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
ostream& operator << (ostream& output, MapLoader& m)
{
	output << "The map name is ..." << m.mapName << endl;
	return output;
}

ostream& operator<<(ostream& output, ConquestFileReader& cq)
{
	output << "The conquest map name is " << cq.mapName << endl;
	return output;
}

ostream& operator<<(ostream& output, ConquestFileReaderAdapter& cq)
{
	output << "Conquest File Reader Adapter" << endl;
	return output;
}


/// <summary>
/// Copy Constructor
/// </summary>
/// <param name="map">Map pointer</param>
MapLoader::MapLoader(const MapLoader& map) {

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

	if (!s.empty()) {
		words.push_back(s);
	}
	
	return words;
}

ConquestFileReader::ConquestFileReader() {
	mapName = "";
	parsedMap = new Map();
}

ConquestFileReader::ConquestFileReader(std::string mapName) {
	this->mapName = mapName;
	parsedMap = new Map();
}
ConquestFileReader::~ConquestFileReader() {
	if (parsedMap != NULL)
		delete parsedMap;
	parsedMap = NULL;
}

ConquestFileReader::ConquestFileReader(const ConquestFileReader& map)
{
	cout << "Copy constructor is being called...\n" << endl;
	this->mapName = map.mapName;
	this->parsedMap = map.parsedMap;
}

ConquestFileReader& ConquestFileReader::operator=(const ConquestFileReader fileReader)
{
	//check for self-assignment
	if (this == &fileReader)
		return *this;

	//copying
	mapName = fileReader.mapName;
	parsedMap = fileReader.parsedMap;

	return *this;
}


Map* ConquestFileReader::readConquestMap(std::string mapFilePath)
{
	parsedMap = new Map();
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
	cout << "Name of the file: " << mapFilePath << endl;
	cout << endl;
	if (openFile.is_open()) {
		while (getline(openFile, line)) {
			if (line.find("[Continents]") == 0) {

				cout << "Found the continent section...\n" << endl;
				int continentId = 0;
				while (getline(openFile, line)) {
					if (line.length() != 0) {
						std::string info = line;
						std::vector<string> words = ConquestFileReader::split(line, "=");

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

						if (continentId > 32) {
							cout << "The file has surpassed the maximum continent limit of 32.\n" << endl;
							return NULL;
						}
					}
					else {

						cout << "Finished adding continents.\n" << endl;
						break;
					}
				}
			}
			std::vector<string> boardersname;

			if (line.find("[Territories]") == 0) {
				cout << "Found the territories section...\n" << endl;
				int territoryId = 1;
				int continentId = 1;

				while (getline(openFile, line)) {
					if (line.length() != 0) {
						std::string info = line;
						std::vector<string> words = ConquestFileReader::split(line, ",");

						if (words.size() < NUM_ENTRIES_TERRITORIES) {
							cout << "The file has invalid territory information.\n" << endl;
							exit(1);
						}
						std::map<int, Continent*> cont = parsedMap->getContinents();
						std::map<int, Continent*>::iterator it = cont.begin();

						while (it != cont.end()) {
							std::string word = it->second->name;
							if (word == words[3]) {
								continentId = it->first;
							}
							it++;
						}

						//Adding territory to map object, 
						//0 is the territory id, 
						//1 is the name, 
						//2 is the country it belongs to (must match country id generated by map)
						parsedMap->addTerritory(words[0], territoryId, continentId);

						cout << "Adding country number " << territoryId << "\n" << endl;
						cout << "Country name: " << words[0] << "\n" << endl;
						cout << "Country belongs to continent number " << continentId << "\n" << endl;
						int i = 4;
						std::string bord = "";
						while (i < words.size()) {
							bord = bord + words[i] + ",";
							i++;
						}
						boardersname.push_back(bord);
						territoryId++;
					}
					if (territoryId > 255) {
						cout << "The file has surpassed the maximum territory limit of 255.\n" << endl;
						return NULL;
					}

				}
				cout << "Finished adding countries.\n" << endl;

				cout << "Adding the boarders section..." << endl;
				int i = 0;

				while (i < parsedMap->getSize()) {
					std::vector<int> boarders;
					std::vector<string> words = ConquestFileReader::split(boardersname[i], ",");
					int j = 1;
					int count = 0;
					while (words.size() - 1 >= count) {
						if (parsedMap->getTerritory(j)->country == words[count]) {
							boarders.push_back(j);
							j = 0;
							count++;
						}
						j++;

					}
					if (boarders.size() > 10) {
						cout << "The file has a territory that surpassed the maximum border limit of 10.\n" << endl;
						return NULL;
					}
					cout << "Adding borders ";
					for (int j = 0; j < boarders.size(); j++) {
						cout << boarders[j] << " ";
					}
					cout << "to country number " << i + 1 << "\n" << endl;
					parsedMap->addEdges(i + 1, boarders);
					i++;

				}
				cout << "Finished adding borders.\n" << endl;
			}

		}
	}

	openFile.close();
	return parsedMap;
}

Map* ConquestFileReader::loadConquestMap(std::string mapFilePath) {

	cout << "Verifying map before loading...\n" << endl;

	parsedMap = readConquestMap(mapFilePath);

	if (parsedMap == NULL) {
		cout << "Map was NOT successfully generated\n" << endl;
	}
	else {
		cout << "Map successfully generated, returning parsed map...\n" << endl;
	}
	return parsedMap;
}

std::vector<string> ConquestFileReader::split(string s, string delim)
{
	vector<string> words;

	size_t pos = 0;
	std::string token;

	while ((pos = s.find(delim)) != std::string::npos) {

		token = s.substr(0, pos);
		if (token != "")
			words.push_back(token);
		s.erase(0, pos + delim.length());
	}

	if (!s.empty()) {
		words.push_back(s);
	}

	return words;
}

ConquestFileReaderAdapter::ConquestFileReaderAdapter()
{
	reader = nullptr;
}

ConquestFileReaderAdapter::ConquestFileReaderAdapter(ConquestFileReader* rd)
{
	reader = rd;
}

ConquestFileReaderAdapter::~ConquestFileReaderAdapter()
{
	if(reader != nullptr)
		delete reader;
	reader = nullptr;
}

ConquestFileReaderAdapter::ConquestFileReaderAdapter(const ConquestFileReaderAdapter& adapter)
{
	reader = adapter.reader;
}

ConquestFileReaderAdapter& ConquestFileReaderAdapter::operator=(const ConquestFileReaderAdapter fileAdapter)
{
	if (&fileAdapter != this) 
		reader = fileAdapter.reader;
	
		return *this;
}

Map* ConquestFileReaderAdapter::readMap(std::string mapFilePath)
{
	return reader->readConquestMap(mapFilePath);
}

Map* ConquestFileReaderAdapter::loadMap(std::string mapFilePath)
{
	return reader->loadConquestMap(mapFilePath);
}