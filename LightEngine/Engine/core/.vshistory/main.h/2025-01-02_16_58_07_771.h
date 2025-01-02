#pragma once

#include "pch.h"
#include "GameEngine.h"
#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include "crtdbg.h"
extern Light::GameEngine* createApplication();



#include <map>
#include <cstdlib>
#include <new>


// Track allocations
std::map<void*, size_t> allocations;

// Overriding new operator
void* operator new(size_t size) {
    void* ptr = std::malloc(size);
    if (!ptr) throw std::bad_alloc();
    allocations[ptr] = size;
    std::cout << "Allocated " << size << " bytes at " << ptr << std::endl;
    return ptr;
}

// Overriding delete operator
void operator delete(void* ptr) noexcept {
    if (ptr) {
        auto it = allocations.find(ptr);
        if (it != allocations.end()) {
            std::cout << "Deallocated " << it->second << " bytes at " << ptr << std::endl;
            allocations.erase(it);
        }
        else {
            std::cerr << "Error: Double free or invalid delete at " << ptr << std::endl;
        }
        std::free(ptr);
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