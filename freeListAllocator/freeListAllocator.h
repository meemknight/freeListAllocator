#pragma once
#include <mutex>

#define KB(x) (x) * 1024
#define MB(x) KB((x)) * 1024
#define GB(x) MB((x)) * 1024

#define LINK_TO_GLOBAL_ALLOCATOR 1
#define HEAP_SIZE MB(10)

///set this to 0 if you want to compile on other platforms
#define WINDOWS_DYNAMIC_IMPLEMENTATION 1


struct FreeListAllocator
{
	char *baseMemory = 0;

	FreeListAllocator() = default;
	FreeListAllocator(void* baseMemory, size_t memorySize) 
	{
		init(baseMemory, memorySize);
	}

	void init(void* baseMemory, size_t memorySize);
	
	void* allocate(size_t size);

	void free(void* mem);

	void* threadSafeAllocate(size_t size);

	void threadSafeFree(void* mem);

	//if this is false it will crash if it is out of memory
	//if this is true it will return 0 when there is no more memory
	//I rocommand leaving this to false
	bool returnZeroIfNoMoreMemory = false;

private:
	
	void* end = 0;

	std::mutex mu;

	size_t getEnd()
	{
		return (size_t)end;
	}

};


struct FreeListAllocatorWinSpecific
{
	
	FreeListAllocatorWinSpecific() = default;
	FreeListAllocatorWinSpecific(size_t memorySize)
	{
		init(memorySize);
	}

	void init(size_t memorySize);

	void* allocate(size_t size);

	void free(void* mem);

	void* threadSafeAllocate(size_t size);

	void threadSafeFree(void* mem);
	
	///returns 0 if fails
	bool extendAllocatedMemory(size_t size);

private:
	FreeListAllocator allocator;
	void* endOfReservedSpace;
	void* endOfAllocatedSpace;
	void* beginOfAllocatedSpace;

};

