#include "pch.h"
#include "SFMLWindow.h"

Light::SFMLWindow::SFMLWindow(const std::string &title, Rectangle rect, std::shared_ptr<SFMLRenderer> renderer, std::shared_ptr<Scene> currentScene)
	: Window(title, rect, renderer, currentScene) { }

Light::SFMLWindow::SFMLWindow(const std::string &title, Rectangle rect, std::shared_ptr<SFMLRenderer> renderer)
	: Window(title, rect, renderer) { }


Light::SFMLWindow::SFMLWindow(const std::string& title, Rectangle rect, std::shared_ptr<Scene> currentScene)
	: Window(title, rect, currentScene) { }

Light::SFMLWindow::SFMLWindow(const std::string& title, Rectangle rect)
	: Window(title, rect) { }


Light::SFMLWindow::~SFMLWindow()
{
	delete m_window;
}


void Light::SFMLWindow::render() {
	m_renderer->render();
}

bool Light::SFMLWindow::isOpen()
{
	return m_window->isOpen();
}

void Light::SFMLWindow::close()
{
	m_window->close();
}

void Light::SFMLWindow::update()
{
	sf::Event event;
	while (m_window->pollEvent(event)) {
		//TODO: Call imgui's event handling
		/*
			
			ImGui::SFML::ProcessEvent(window, event);

		*/
		if (event.type == sf::Event::Closed) {
			m_window->close();
		}
	}
}

bool Light::SFMLWindow::hasFocus() {
	return m_window->hasFocus();
}

void Light::SFMLWindow::clear()
{
	m_window->close();
}

void Light::SFMLWindow::initWindow()
{
	m_window = new sf::RenderWindow(sf::VideoMode(m_rect.width, m_rect.height), m_title);
}
