#include "Engine.h"
#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "Engine/data/Sequence.h"
#include "Engine/ECS/components/specific/position/GlobalPositionComponent.h"


class Game : public Light::GameEngine
{
public:
	Game() {
		std::cout << "hello" << std::endl;
        

        Light::PriorityQueue<int> queue;

        queue << 3 << 5 << 8 << 10;
     
        for (auto it = queue.begin(); it != queue.end(); ++it) {
            std::cout << *it << std::endl;
        }

        Light::ECSCoordinator coordinator;
        Light::EntityHandler handler = coordinator.createEntity();
        handler.add(Light::GlobalPositionComponent(600, 200));




        sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3"); // add Style::None for borderless.
        //window.setFramerateLimit(60);
        ImGui::SFML::Init(window);
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);

        sf::Clock deltaClock;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                ImGui::SFML::ProcessEvent(window, event);

                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            if (Light::Input::isKeyPressed(Light::Key::A)) {
                std::cout << " A key is pressed! " << std::endl;
            }

            ImGui::SFML::Update(window, deltaClock.restart());

            ImGui::ShowDemoWindow();

            ImGui::Begin("Hello, world!");
            ImGui::Button("Look at this pretty button");
            ImGui::End();

            window.clear();
            window.draw(shape);
            ImGui::SFML::Render(window);
            window.display();
        }

        ImGui::SFML::Shutdown();
	}
	~Game() {

	}

private:

};



KICKOFF(Game)
