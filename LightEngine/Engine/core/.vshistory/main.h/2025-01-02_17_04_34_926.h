#pragma once

#include "pch.h"
#include "GameEngine.h"
#include <iostream>
#define DEBUG_NEW new(__FILE__, __LINE__)
#define new DEBUG_NEW
extern Light::GameEngine* createApplication();



#include <map>
#include <cstdlib>
#include <new>




int main(int argc, char** argv) {
	

	Light::GameEngine* engine = Light::createApplication();
	



	return 1;
}