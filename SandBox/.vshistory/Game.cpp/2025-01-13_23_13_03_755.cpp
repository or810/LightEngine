#include "Engine.h"
#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "Engine/data/Sequence.h"

#include "Engine/EntityComponentSystem/ECSCoordinator.h"

struct Pos {
    int x, y;
};

class Game : public Light::GameEngine
{
public:
	Game() {

        //Light::PriorityQueue<int> queue;

        //queue << 3 << 5 << 8 << 10;
     
        //for (auto it = queue.begin(); it != queue.end(); ++it) {
        //    std::cout << *it << std::endl;
        //}

        
        Light::ECS::ECSCoordinator* coordinator = new Light::ECS::ECSCoordinator();
        Pos pos = { 5,2 };
        std::cout << sizeof(pos);
        coordinator->registerComponent<Pos>();
        Light::ECS::Entity entity = coordinator->createEntity();
        Light::ECS::EntityHandler handler = coordinator->getEntityHandler(entity);
        handler.addComponent<Pos>(pos);
        //Pos pos = { 20, 40 };
        //handler.add(pos);
        



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
