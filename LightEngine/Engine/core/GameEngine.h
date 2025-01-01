#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../scenary/Scene.h"

#define KICKOFF(X) \
    Light::GameEngine* Light::createApplication() { return new X(); }


namespace Light {

	class EngineParams {
	public:
		std::string name;

		EngineParams(std::string n)
			: name(n)
		{
		}
	};

	class GameEngine
	{
	public:
		GameEngine();
		~GameEngine();

		void setParams(EngineParams params);
	private:
		bool m_isRunning;
		EngineParams* params;
		std::vector<std::shared_ptr<Scene>> scenes;

	private:
		static GameEngine* s_instance;
	};

	GameEngine* createApplication();
}
