#pragma once

#include "pch.h"
#include "GameEngine.h"
#include <iostream>

extern Light::GameEngine* createApplication();

int main(int argc, char** argv) {

	Light::GameEngine* engine = Light::createApplication();

	return 1;
}