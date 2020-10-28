#include <iostream>
#include "freeListAllocator.h"
#include <algorithm>
#include <array>
#include <random>
#include <map>
#include <sstream>
#include <vector>

const char* randThings[] = { "string1", "2", "o chestie mai mare aici", "ceva si mai mare",
"mic", "12", "lorem lipsum dolores etc etc", "lorem lipsum dolores etc etc lorem ipsum dolores etc etc", 
"lorem lipsum dolores etc etc lorem ipsum dolores etc etc lorem lipsum dolores etc etc lorem ipsum dolores etc etc" };

int main()
{
	
	std::map<std::string, int> map;
	
	std::string test = "test";

	for(int i=0; i<100; i++)
	{
		
		map[test + std::to_string(i)] = i;
	
	
	}
	
	std::vector<std::string> v;

	for(auto c : map)
	{
		v.push_back(c.first);
	}

	map.clear();

	for (int l = 0; l < 30; l++)
	{
		for (int i = 0; i < 30; i++)
		{
			int rng = rand() % v.size();

			v.erase(v.begin() + i);

		}

		for (int i = 0; i < 30; i++)
		{
			int r = sizeof(randThings) / sizeof(randThings[0]);

			v.push_back(v[r]);

		}

	}



	return 0;
}