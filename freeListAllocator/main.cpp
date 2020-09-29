#include <iostream>
#include "freeListAllocator.h"

#define KB(x) (x) * 1024
#define MB(x) KB((x)) * 1024



int main()
{
	char memBlock[120] = {};


	FreeListAllocator allocator;
	allocator.init(memBlock, sizeof(memBlock));
	
	while(true)
	{
		char* a = (char*)allocator.allocate(8);

		a[0] = 'X';
		a[1] = 'x';
		a[2] = 'x';
		a[3] = 'x';
		a[4] = 'x';
		a[5] = 'x';
		a[6] = 'x';
		a[7] = 'x';

		allocator.free(a);
	
	}

	char *a = (char*)allocator.allocate(8);

	a[0] = 'X';
	a[1] = 'x';
	a[2] = 'x';
	a[3] = 'x';
	a[4] = 'x';
	a[5] = 'x';
	a[6] = 'x';
	a[7] = 'x';


	char *b = (char*)allocator.allocate(40);

	allocator.free(b);


	allocator.allocate(8);

	//allocator.allocate(4);



}