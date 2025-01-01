#include "pch.h"
#include "Application.h"
#include <thread>

Light::Application::Application(int width, int height, std::unique_ptr<Window> window)
	: m_width(width), m_height(height), m_window(std::move(window)) { }

void Light::Application::update(DeltaTime dt)
{
    //TODO: implement update.
}

void Light::Application::render()
{
    //TODO: implement render.
}

void Light::Application::run(unsigned int maxUpdates, unsigned int maxFrames)
{
    double timePerUpdate = 1000000000.0 / maxUpdates; // Time per update in nanoseconds
    double timePerFrame = 1000000000.0 / maxFrames;   // Time per frame in nanoseconds

    long long lastUpdateTime = getCurrentTimeInNanoseconds();
    long long lastFrameTime = getCurrentTimeInNanoseconds();
    double deltaUpdate = 0;
    double deltaFrame = 0;

    int64_t lastStatsTime = getCurrentTimeInMilliseconds();
    int updateCount = 0;  // Initialize update count
    int frameCount = 0;    // Initialize frame count

    while (true) {
        auto now = getCurrentTimeInNanoseconds();
        deltaUpdate += (now - lastUpdateTime) / timePerUpdate;
        deltaFrame += (now - lastFrameTime) / timePerFrame;

        lastUpdateTime = now; // Update last update time here

        // Update the game state
        while (deltaUpdate >= 1) {
            //----------------------- UPDATE -------------------------/
            update(DeltaTime(deltaUpdate / 1.0)); // Pass delta time as DeltaTime object
            //-------------------------------------------------------/
            updateCount++;
            deltaUpdate--;
        }

        // Render the scene if enough time has passed
        if (deltaFrame >= 1) {
            //----------------------- RENDER -------------------------/
            render();
            //-------------------------------------------------------/
            frameCount++;
            deltaFrame--;
        }

        // Check for statistics update
        if (getCurrentTimeInMilliseconds() - lastStatsTime >= 1000) {
            std::printf("UPS: %d, FPS: %d\n", updateCount, frameCount);
            updateCount = 0;
            frameCount = 0;
            lastStatsTime = getCurrentTimeInMilliseconds();
        }

        // Sleep to avoid busy waiting
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

}


void Light::Application::run(unsigned int maxUpdates)
{
    double timePerUpdate = 1000000000.0 / maxUpdates; // Time per update in nanoseconds

    long lastUpdateTime = getCurrentTimeInNanoseconds();
    double deltaUpdate = 0;

    int64_t lastStatsTime = getCurrentTimeInMilliseconds();
    int updateCount = 0;  // Initialize update count

    while (true) {
        auto now = getCurrentTimeInNanoseconds();
        deltaUpdate += (now - lastUpdateTime) / timePerUpdate;
        lastUpdateTime = now; // Update last update time here

        // Update the game state
        while (deltaUpdate >= 1) {
            //----------------------- UPDATE -------------------------/
            update(DeltaTime(deltaUpdate / 1.0)); // Pass delta time as DeltaTime object
            //-------------------------------------------------------/
            updateCount++;
            deltaUpdate--;
        }

        // Render the scene as frequently as possible
        //----------------------- RENDER -------------------------/
        render();
        //-------------------------------------------------------/

        // Check for statistics update
        if (getCurrentTimeInMilliseconds() - lastStatsTime >= 1000) {
            std::printf("UPS: %d\n", updateCount);
            updateCount = 0;
            lastStatsTime = getCurrentTimeInMilliseconds();
        }

        // Sleep to avoid busy waiting
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

