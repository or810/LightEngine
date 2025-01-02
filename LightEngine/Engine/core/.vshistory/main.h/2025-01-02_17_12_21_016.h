#pragma once

#include "pch.h"
#include "GameEngine.h"
#include <iostream>
extern Light::GameEngine* createApplication();



#include <map>
#include <cstdlib>
#include <new>




int main(int argc, char** argv) {
	

	Light::GameEngine* engine = Light::createApplication();
	
	int a = 3;


	return 1;
}