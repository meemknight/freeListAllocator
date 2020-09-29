#include <iostream>
#include "freeListAllocator.h"
#include <algorithm>
#include <array>

#define KB(x) (x) * 1024
#define MB(x) KB((x)) * 1024



int main()
{
	char memBlock[KB(2)] = {};

	FreeListAllocator allocator;
	allocator.init(memBlock + 1, sizeof(memBlock) - 1);

	constexpr int allocations = 20;
	constexpr int testsNr = 2000;

	std::array<void*, allocations> ptrs;

	for(int test =0; test< testsNr; test++)
	{
		for(int i=0; i< allocations; i++)
		{
			ptrs[i] = allocator.allocate(12);
		}

		std::random_shuffle(ptrs.begin(), ptrs.end());

		for (int i = 0; i < allocations; i++)
		{
			allocator.free(ptrs[i]);
		}

	}

	//check integrity

	allocator.allocate(KB(2) - 46);


	//allocator.allocate(4);


	return 0;
}