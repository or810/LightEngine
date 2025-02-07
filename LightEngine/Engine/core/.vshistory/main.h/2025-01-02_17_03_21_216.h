#pragma once

#include "pch.h"
#include "GameEngine.h"
#include <iostream>

extern Light::GameEngine* createApplication();



#include <map>
#include <cstdlib>
#include <new>


std::map<void*, size_t> allocations;

void* operator new(size_t size) {
    void* ptr = std::malloc(size);
    if (!ptr) throw std::bad_alloc();

    // Track allocation with its size
    allocations[ptr] = size;

    std::cout << "Allocated " << size << " bytes at " << ptr << std::endl;
    return ptr;
}

void operator delete(void* pointer) noexcept {
    if (pointer) {
        // Find the allocation size from the map
        auto it = allocations.find(pointer);
        if (it != allocations.end()) {
            size_t size = it->second;
            std::cout << "Deallocated " << size << " bytes at " << pointer << std::endl;

            // Remove from map
            allocations.erase(it);
        }
        else {
            std::cerr << "Error: Double free or invalid delete at " << pointer << std::endl;
        }

        // Perform the actual deallocation
        std::free(pointer);
    }
}

void checkMemoryLeaks() {
    if (!allocations.empty()) {
        std::cout << "Memory Leaks Detected:\n";
        for (const auto& allocation : allocations) {
            std::cout << "Leaked " << allocation.second << " bytes at " << allocation.first << std::endl;
        }
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