#pragma once

#include "pch.h"
#include "GameEngine.h"
#include <iostream>
extern Light::GameEngine* createApplication();

int main(int argc, char** argv) {
	
	std::cout << "starting..." << "\n";

	Light::GameEngine* engine = Light::createApplication();
	
	return 1;
}