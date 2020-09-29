#include <iostream>
#include "freeListAllocator.h"

#define KB(x) (x) * 1024
#define MB(x) KB((x)) * 1024



int main()
{
	char memBlock[120] = {};

	FreeListAllocator allocator;
	allocator.init(memBlock, sizeof(memBlock));
	
	while(1)
	{
	

		char* a = (char*)allocator.allocate(8);	
		char* b = (char*)allocator.allocate(8);
	
	
		allocator.free(a);
		allocator.free(b);
	
		char* c = (char*)allocator.allocate(60);
		allocator.free(c);


	}



	while(1)
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







	allocator.allocate(8);

	//allocator.allocate(4);



}