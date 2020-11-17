#include <iostream>
#include "freeListAllocator.h"
#include <algorithm>
#include <array>
#include <random>


char memBlock[KB(2)] = {};
FreeListAllocator allocator(memBlock, sizeof(memBlock));

//todo (vlod): Add c++17 overloads
//todo add own assert

void* operator new  (std::size_t count)
{
	auto a = allocator.threadSafeAllocate(count);

	//std::cout << "Allocated " << count << " at " << a << '\n';

	return a;
}

void* operator new[](std::size_t count)
{
	auto a = allocator.threadSafeAllocate(count);

	//std::cout << "Allocated " << count << " at " << a << '\n';

	return a;
}

void operator delete  (void* ptr)
{
	//std::cout << "Deallocated at: " << ptr << "\n";

	allocator.threadSafeFree(ptr);
}

void operator delete[](void* ptr)
{
	//std::cout << "Deallocated at: " << ptr << "\n";

	allocator.threadSafeFree(ptr);
}



int main()
{
	
	{
		std::string s = "12345678123456781234567812345678";
		std::cout << s << "\n";
		std::string s2 = "12345678123456781234567812345678";
		std::string s3 = "12345678123456781234567812345678";
		std::string s4 = "12345678123456781234567812345678";

		s2 = "";
		s2.shrink_to_fit();

		size_t availableMemory = 0;
		size_t biggestBlock = 0;
		int freeBlocks = 0;

		std::cout << "\n\n";

		allocator.calculateMemoryMetrics(availableMemory, biggestBlock, freeBlocks);

		std::cout << "Available: " << availableMemory << "  biggest: " << biggestBlock << " \nfreeBlocks: " << freeBlocks
			<< "\n";

	}


	return 0;
}