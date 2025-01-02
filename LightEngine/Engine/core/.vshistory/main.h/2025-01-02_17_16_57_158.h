#pragma once

#include "pch.h"
#include "GameEngine.h"
#include <iostream>
extern Light::GameEngine* createApplication();



#include <map>
#include <cstdlib>
#include <new>




int main(int argc, char** argv) {
 	int a = 3;

	std::cout << "starting..." << "\n";

	Light::GameEngine* engine = Light::createApplication();
	

	std::cout << "ending" << "\n";

	return 1;
}