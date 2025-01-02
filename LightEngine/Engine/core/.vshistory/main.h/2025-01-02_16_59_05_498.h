#pragma once

#include "pch.h"
#include "GameEngine.h"
#include <iostream>

extern Light::GameEngine* createApplication();



#include <map>
#include <cstdlib>
#include <new>


// Track allocations
static size_t totalAllocations = 0;
static size_t totalDeallocations = 0;

void* operator new(size_t size) {
    totalAllocations += size;
    std::cout << "Allocated " << size << " bytes. Total allocations: " << totalAllocations << " bytes.\n";
    return std::malloc(size);  // Use the default malloc for allocation
}

void operator delete(void* pointer) noexcept {
    std::free(pointer);  // Use the default free for deallocation
}

void checkMemoryLeaks() {
    if (totalAllocations != totalDeallocations) {
        std::cout << "Memory leak detected! "
            << totalAllocations - totalDeallocations << " bytes leaked.\n";
    }
    else {
        std::cout << "No memory leaks detected.\n";
    }
}







int main(int argc, char** argv) {
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Light::GameEngine* engine = Light::createApplication();
	

	checkMemoryLeaks();         // Check for memory leaks


	return 1;
}