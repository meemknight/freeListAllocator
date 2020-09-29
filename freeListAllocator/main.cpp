#include <iostream>
#include "freeListAllocator.h"

#define KB(x) (x) * 1024
#define MB(x) KB((x)) * 1024



int main()
{
	char memBlock[120] = {};


	FreeListAllocator allocator;
	allocator.init(memBlock, sizeof(memBlock));
	
	char *c = (char*)allocator.allocate(8);

	c[0] = 'X';
	c[1] = 'x';
	c[2] = 'x';
	c[3] = 'x';
	c[4] = 'x';
	c[5] = 'x';
	c[6] = 'x';
	c[7] = 'x';

	allocator.allocate(4);
	allocator.allocate(4);



}