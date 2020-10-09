#include "MapLoader.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;

namespace MapLoaderDriver {
	int main() {
		std::cout << "MapLoaderDriver\n" << std::endl;

		//valid map
		ifstream mapFile("Maps\\solar.map");

		try
		{
			Map* map = MapLoader::LoadMap(mapFile);
		}
		catch (const std::exception&)
		{
			cout << "Loading map failed with the following error: " << endl;
			cout << exception << "\n" << endl;
		}

		std::vector<string> invalidMaps;
		
		//invalid maps
		std::string path = "Maps";
		for (auto& entry: fs::directory_iterator(path)) {
			invalidMaps.push_back(entry.path());
		}

		for (size_t i = 0; i < invalidMaps.size; i++)	
		{
			try
			{
				Map* map = MapLoader::LoadMap(invalidMaps[i]);
			}
			catch (const std::exception&)
			{
				cout << "Loading map failed with the following error: " << endl;
				cout << exception << "\n" << endl;
			}
		}

		
		return 1;
	}
}