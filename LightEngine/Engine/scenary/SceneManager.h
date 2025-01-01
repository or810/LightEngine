#pragma once

#include <vector>
#include <algorithm>
#include "Scene.h"

namespace Light {
	class SceneManager
	{
		SceneManager(); // use default scene
		SceneManager(Scene* scene);

		void remove(int index);
		void remove(Scene* scene);

		void push(Scene* scene);

	private:
		void addDefaultScene(); //TODO: Add defualt scene, with the many layers
	private:
		unsigned int focusScene = 0;
		std::vector<Scene*> m_scenes;
	};
}
