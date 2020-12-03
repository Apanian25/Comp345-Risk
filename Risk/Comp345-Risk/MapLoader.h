#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include "Map.h"

using namespace std;


namespace MapLoaderDriver {
	int main();
}

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
	virtual Map* loadMap(std::string mapFilePath);

	std::string mapName;
	friend ostream& operator << (ostream& output, MapLoader &m);

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
	Map* readMap(std::string mapFilePath);

};
class ConquestFileReader {
public:
	ConquestFileReader();
	ConquestFileReader(std::string mapName);
	~ConquestFileReader();
	ConquestFileReader(const ConquestFileReader& map);
	ConquestFileReader& operator=(const ConquestFileReader fileReader);

	std::string mapName;
	friend ostream& operator << (ostream& output, ConquestFileReader& cq);

	Map* readConquestMap(std::string mapFilePath);
	Map* loadConquestMap(std::string mapFilePath);
private:
	std::vector<string> split(string s, string delim);
	static const int NUM_ENTRIES_CONTINENT = 2;
	static const int NUM_ENTRIES_TERRITORIES = 4;
	Map* parsedMap;
};



class ConquestFileReaderAdapter :public MapLoader {
private:
	ConquestFileReader* reader;
public:
	ConquestFileReaderAdapter();
	ConquestFileReaderAdapter(ConquestFileReader* rd);
	~ConquestFileReaderAdapter();
	ConquestFileReaderAdapter(const ConquestFileReaderAdapter& adapter);

	ConquestFileReaderAdapter& operator=(const ConquestFileReaderAdapter fileAdapter);
	friend ostream& operator << (ostream& output, ConquestFileReaderAdapter& cq);

	Map* readMap(std::string mapFilePath);
	Map* loadMap(std::string mapFilePath);
};
