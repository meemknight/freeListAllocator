#include <iostream>
#include "freeListAllocator.h"
#include <algorithm>
#include <array>
#include <random>

#define KB(x) (x) * 1024
#define MB(x) KB((x)) * 1024

char memBlock[MB(10)] = {};
FreeListAllocator allocator(memBlock, sizeof(memBlock));

void* operator new  (std::size_t count)
{
	auto a = allocator.allocate(count);
	
	std::cout << "Allocated " << count << " at " << a << '\n';
	
	return a;
}

void* operator new[](std::size_t count)
{
	auto a = allocator.allocate(count);

	std::cout << "Allocated " << count << " at " << a << '\n';

	return a;
}

void operator delete  (void* ptr)
{
	std::cout << "deallocated at: " << ptr << "\n";

	allocator.free(ptr);
}

void operator delete[](void* ptr) 
{
	std::cout << "deallocated at: " << ptr << "\n";

	allocator.free(ptr);
}



int main()
{
	//char* bonus = new char[34];
	//
	//
	//char* a = new char[8]{};	// 1
	//
	//char* b = new char[15]{};	// 2
	//
	//delete[] a;					// 3
	//
	//char *c = new char[52]{};	// 4
	//
	//delete[] b;					// 5
	//
	//char* d = new char[76]{};	// 6
	//
	//delete[] c;					// 7
	//
	//char *e= new char[213]{};
	//
	//delete[] d;
	//delete[] e;
	//delete[] bonus;

	std::vector<int> test;
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	test.push_back(4);
	test.push_back(5);
	test.push_back(6);
	test.push_back(7);
	test.push_back(8);
	test.push_back(9);
	test.push_back(10);
	test.push_back(11);
	test.push_back(12);
	test.push_back(13);
	test.push_back(14);
	test.push_back(15);
	test.push_back(16);
	test.push_back(17);
	test.push_back(18);

	return 0;
}