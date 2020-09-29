#pragma once


struct FreeListAllocator
{
	char *baseMemory;
	size_t memorySize;

	FreeListAllocator() = default;

	void init(void* baseMemory, size_t memorySize);
	
	void* allocate(size_t size);

	void free(void* mem);

private:
	
	void* end;

	size_t getEnd()
	{
		return (size_t)end;
	}

};

