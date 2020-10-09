#include "MapLoader.h"
#include "Map.h"
#include <iostream>

namespace MapLoaderDriver {
	int main() {
		std::cout << "MapLoaderDriver" << std::endl;

		ifstream mapFile("Maps\\solar.map");

		try
		{
			Map* map = MapLoader::LoadMap(mapFile);
		}
		catch (const std::exception&)
		{
			cout << "Loading map failed with the following error: " << endl;
			cout << exception << endl;
		}
		

		
		return 1;
	}
}