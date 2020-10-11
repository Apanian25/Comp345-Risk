#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include "Map.h"

using namespace std;

class MapLoader {

public:
	//default constructor
	MapLoader();
	//constructor
	MapLoader(std::string mapName);
	//destructor
	~MapLoader();
	//copy constructor
	MapLoader(const MapLoader &map);
	//Overloading assignment operator
	MapLoader& operator= (const MapLoader& mapLoader);

	//method to be called by other classes to load a parsed map
	Map* LoadMap(std::string mapFilePath);

	std::string mapName;
	friend istream& operator << (istream& in, MapLoader &m);

private:
	static const int NUM_ENTRIES_CONTINENT = 3;
	static const int NUM_ENTRIES_TERRITORIES = 3;
	std::vector<string> split(string s, string delim);
	Map* parsedMap;

	enum ContinentEntries {
		Name = 0,
		Country = 1,
		ArmyNumber = 2,
	};

	//read the map file - reject if not playable or missing headers/continents/countries/borders
	Map* ReadMap(std::string mapFilePath);

};