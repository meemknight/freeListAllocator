# freeListAllocator

A simple 8 byte aligned allocator that manages a block of memory.
You have the option to overload the global new/delete. If you do that you might b=have problems if you have globals that allocate memory.
