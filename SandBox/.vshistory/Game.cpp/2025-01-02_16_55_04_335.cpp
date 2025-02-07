#include "Engine.h"
#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "Engine/data/Sequence.h"
#include <map>
#include <cstdlib>
#include <new>

std::map<void*, size_t> allocations;

void* operator new(size_t size) {
    void* ptr = std::malloc(size);
    if (!ptr) throw std::bad_alloc();
    allocations[ptr] = size; // Track allocation
    std::cout << "Allocated " << size << " bytes at " << ptr << std::endl;
    return ptr;
}

void operator delete(void* ptr) noexcept {
    if (ptr) {
        auto it = allocations.find(ptr);
        if (it != allocations.end()) {
            std::cout << "Deallocated " << it->second << " bytes at " << ptr << std::endl;
            allocations.erase(it); // Remove from the tracking map
        }
        else {
            std::cerr << "Error: Double free or invalid delete at " << ptr << std::endl;
        }
        std::free(ptr);
    }
}

void operator delete(void* ptr, size_t size) noexcept {
    operator delete(ptr);
}


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
