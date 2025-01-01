#include "Engine.h"
#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>


#include "Engine/data/Sequence.h"

class Game : public Light::GameEngine
{
public:
	Game() {
		std::cout << "hello" << std::endl;
        


       /* Light::BinarySearchTree<int, std::greater<uint32_t>> tree;
        tree.insert(1, 0);
        tree.insert(2, 1);
        tree.insert(3, 20);
        tree.insert(4, 3);
        tree.insert(5, 4);
        std::cout << "Forward Iteration" << std::endl;
        for (auto it = tree.begin(); it != tree.end(); ++it) {
            std::cout << *it << std::endl;
        }*/

        Light::PriorityQueue<double> queue;

        queue << 3.87 << 5.2 << 8.1 << 10.2;
     
        for (auto it = queue.begin(); it != queue.end(); ++it) {
            std::cout << it.priority() << std::endl;
        }





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
