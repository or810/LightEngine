#pragma once

#include "../../Window.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "SFMLRenderer.h"

namespace Light {
	class SFMLWindow : public Window
	{
		SFMLWindow(const std::string& title, Rectangle rect, std::shared_ptr<SFMLRenderer> renderer, std::shared_ptr<Scene> currentScene);
		SFMLWindow(const std::string& title, Rectangle rect, std::shared_ptr<SFMLRenderer> renderer);
		SFMLWindow(const std::string& title, Rectangle rect, std::shared_ptr<Scene> currentScene);
		SFMLWindow(const std::string& title, Rectangle rect);

		~SFMLWindow();

		bool hasFocus();

		void initWindow();

		void render();

		bool isOpen();

		void close();

		void update();

		void clear();
	private:
		sf::RenderWindow* m_window;
	};
}

