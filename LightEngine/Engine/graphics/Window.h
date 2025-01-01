#pragma once
#include <memory>
#include "../scenary/Scene.h"
#include "../data/Rectangle.h"
#include "Renderer.h"
#include <string>

namespace Light {
	class Window
	{
	public:

		unsigned int getWidth() { return m_rect.width; }
		unsigned int getHeight() { return m_rect.height; }
		unsigned int getX() { return m_rect.x; }
		unsigned int getY() { return m_rect.y; }


	protected:
		Window(const std::string &title, Rectangle rect, std::shared_ptr<Renderer> renderer, std::shared_ptr<Scene> currentScene)
			: m_title(title), m_rect(rect), m_renderer(renderer), m_currentScene(currentScene) 
		{
			initWindow();
		}

		Window(const std::string &title, Rectangle rect, std::shared_ptr<Renderer> renderer)
			: m_title(title), m_rect(rect), m_renderer(renderer) 
		{
			initWindow();
		}

		Window(const std::string& title, Rectangle rect, std::shared_ptr<Scene> currentScene)
			: m_title(title), m_rect(rect), m_currentScene(currentScene)
		{
			initWindow();
			//TODO: Make an instance of renderer.
		}
		Window(const std::string &title, Rectangle rect)
			: m_title(title), m_rect(rect) 
		{
			initWindow();
			//TODO: Make an instance of renderer.
		}

		virtual void initWindow() = 0;

		virtual bool isOpen() = 0;

		virtual void close() = 0;

		virtual void update() = 0;

		virtual void clear() = 0;

	protected:
		std::shared_ptr<Scene> m_currentScene;
		std::shared_ptr<Renderer> m_renderer;
		const std::string &m_title;
		Rectangle m_rect;
	};
}
