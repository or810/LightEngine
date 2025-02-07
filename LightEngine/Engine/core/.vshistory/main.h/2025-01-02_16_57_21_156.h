#pragma once

#include "pch.h"
#include "GameEngine.h"
#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include "crtdbg.h"
extern Light::GameEngine* createApplication();

int main(int argc, char** argv) {
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Light::GameEngine* engine = Light::createApplication();

	return 1;
}