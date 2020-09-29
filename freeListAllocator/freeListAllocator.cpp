#include "freeListAllocator.h"
#include <cassert>
#include <cstdint>
#include <iostream>

const uint64_t DUMMY_VALUE = 0xff'ff'ff'ff'ff'ff'ff'ff;

struct FreeBlock
{
	union 
	{
		char* next;
		std::uint64_t dummy_;
	};
	std::uint64_t size;

};

struct AllocatedBlock
{
	std::uint64_t size;
	std::uint64_t dummy_;
};


void FreeListAllocator::init(void* baseMemory, size_t memorySize)
{
	end = (void*)((size_t)baseMemory + memorySize);

	assert(sizeof(FreeBlock) == sizeof(AllocatedBlock));
	assert(memorySize > 100);

	this->baseMemory = (char*)baseMemory;
	this->memorySize = memorySize;

	//move base memory to a 8 byte aligned

	size_t pos = (int)this->baseMemory;
	
	if(pos % 8 != 0)
	{
		this->baseMemory += 8-(pos%8);
		this->memorySize -= 8-(pos%8);
	}

	((FreeBlock*)this->baseMemory)->next = nullptr;
	((FreeBlock*)this->baseMemory)->size = this->memorySize-sizeof(FreeBlock);


}

void* FreeListAllocator::allocate(size_t size)
{
	FreeBlock *last = nullptr;
	FreeBlock *current = (FreeBlock*)baseMemory;
	FreeBlock *next = nullptr;

	int aligned8Size = size;
	if (aligned8Size % 8 != 0)
	{
		aligned8Size += (8 - (aligned8Size % 8));
	}

	while(true)
	{
	

		if (aligned8Size <= ((FreeBlock*)current)->size) // this is a suitable block
		{
			//add block here
			next = (FreeBlock*)current->next;

			if(next == nullptr) //this is the last block
			{
				if(last == nullptr) //this is also the first block so move the base pointer
				{
					void* toReturn = (char*)current + sizeof(AllocatedBlock);
					((AllocatedBlock*)current)->size = aligned8Size;	//size of the new allocated block
					((AllocatedBlock*)current)->dummy_ = DUMMY_VALUE;

					FreeBlock* nextFreeBlock = (FreeBlock*)((char*)toReturn + aligned8Size); 
					//next free block is the base memory now

					baseMemory = (char*)nextFreeBlock;
					((FreeBlock*)baseMemory)->next = nullptr; //this is the last block

					size_t size = this->getEnd() - (size_t)nextFreeBlock - (size_t)sizeof(FreeBlock); //set the size of the new last block
					((FreeBlock*)baseMemory)->size = size;

					return toReturn;
				}else //this is not the first block so change the last block pointer
				{
					void* toReturn = (char*)current + sizeof(AllocatedBlock);
					((AllocatedBlock*)current)->size = aligned8Size;	//size of the new allcoated block
					((AllocatedBlock*)current)->dummy_ = DUMMY_VALUE;

					FreeBlock* nextFreeBlock = (FreeBlock*)((char*)toReturn + aligned8Size);

					last->next = (char*)nextFreeBlock; //last is relinked
					nextFreeBlock->next = nullptr; //this is the last block
				
					size_t size = this->getEnd() - (size_t)nextFreeBlock - (size_t)sizeof(FreeBlock); //set the size of the new last block
					nextFreeBlock->size = size;

				}
				
			}else //this is not the last free block 
			{
				
				if(last == nullptr) // this is the first free block but not the last
				{
					void* toReturn = (char*)current + sizeof(AllocatedBlock);
					((AllocatedBlock*)current)->size = aligned8Size;	//size of the new allocated block
					((AllocatedBlock*)current)->dummy_ = DUMMY_VALUE;

					FreeBlock* nextFreeBlock = (FreeBlock*)((char*)toReturn + aligned8Size);
					//next free block is the base memory now

					baseMemory = (char*)nextFreeBlock;
					((FreeBlock*)baseMemory)->next = (char*)next; //this is not the last block

					size_t size = this->getEnd() - (size_t)nextFreeBlock - (size_t)sizeof(FreeBlock); //set the size of the new last block
					((FreeBlock*)baseMemory)->size = size;
				}else // this is not the first free block and not the last 
				{
					void* toReturn = (char*)current + sizeof(AllocatedBlock);
					((AllocatedBlock*)current)->size = aligned8Size;	//size of the new allcoated block
					((AllocatedBlock*)current)->dummy_ = DUMMY_VALUE;

					FreeBlock* nextFreeBlock = (FreeBlock*)((char*)toReturn + aligned8Size);

					last->next = (char*)nextFreeBlock; //last is relinked
					nextFreeBlock->next = (char*)next; //this is not the last block

					size_t size = this->getEnd() - (size_t)nextFreeBlock - (size_t)sizeof(FreeBlock); //set the size of the new last block
					nextFreeBlock->size = size;
				}
			}

		}else
		{
			if(current->next == nullptr)
			{
				//that was the last block, no size
				std::cout << "no more memory";
				assert(0);
			}else
			{
				last = current;
				current = (FreeBlock*)current->next;
				next = (FreeBlock*)current->next;
			
			}
		
		}


	}


	return nullptr;
}

void FreeListAllocator::free(void* mem)
{
}
