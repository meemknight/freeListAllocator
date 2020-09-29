#include <iostream>
#include "freeListAllocator.h"

#define KB(x) (x) * 1024
#define MB(x) KB((x)) * 1024



int main()
{
	char memBlock[120] = {};

	FreeListAllocator allocator;
	allocator.init(memBlock+1, sizeof(memBlock)-1);
	
	while(1)
	{

		char* a = (char*)allocator.allocate(8);	
		char* b = (char*)allocator.allocate(8);
	
		allocator.free(a);
		allocator.free(b);
	
		char* c = (char*)allocator.allocate(60);
		allocator.free(c);


		b = (char*)allocator.allocate(8);
		a = (char*)allocator.allocate(8);
		c = (char*)allocator.allocate(30);

		allocator.free(a);
		allocator.free(b);
		allocator.free(c);

		b = (char*)allocator.allocate(8);
		a = (char*)allocator.allocate(8);
		c = (char*)allocator.allocate(30);

		allocator.free(c);
		allocator.free(b);
		allocator.free(a);

		b = (char*)allocator.allocate(8);
		a = (char*)allocator.allocate(8);
		c = (char*)allocator.allocate(30);

		allocator.free(b);
		allocator.free(a);
		allocator.free(c);

		b = (char*)allocator.allocate(8);
		a = (char*)allocator.allocate(8);
		c = (char*)allocator.allocate(8);
		char* d = (char*)allocator.allocate(8);

		allocator.free(a);
		allocator.free(b);
		allocator.free(d);
		allocator.free(c);

		b = (char*)allocator.allocate(8);
		a = (char*)allocator.allocate(8);
		c = (char*)allocator.allocate(8);
		d = (char*)allocator.allocate(8);

		allocator.free(c);
		allocator.free(d);
		allocator.free(b);
		allocator.free(a);

	}





	allocator.allocate(8);

	//allocator.allocate(4);



}