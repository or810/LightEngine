#pragma once
#include <memory>
#include <chrono>
#include <Engine/graphics/Window.h>
#include <Engine/data/DeltaTime.h>

namespace Light {
	class Application
	{
		// TODO: Have a builder class for Application.

		Application(int width, int height, std::unique_ptr<Window> window);
		~Application() = default;

		void update(DeltaTime dt);

		void render();

	private:

		void run(unsigned int maxUpdates, unsigned int maxFrames);

		void run(unsigned int maxUpdates);

		static double getCurrentTimeInSeconds() {
			// Get the current time point from high_resolution_clock
			auto now = std::chrono::high_resolution_clock::now();

			// Convert to time since epoch in seconds as a double
			auto duration = now.time_since_epoch();
			double seconds = std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();

			return seconds;
		}

		static long long getCurrentTimeInNanoseconds() {
			return std::chrono::duration_cast<std::chrono::nanoseconds>(
				std::chrono::high_resolution_clock::now().time_since_epoch())
				.count();
		}

		static int64_t getCurrentTimeInMilliseconds() {
			return std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::high_resolution_clock::now().time_since_epoch())
				.count();
		}

	private:
		int m_width;
		int m_height;

		int updateCount; 
		int frameCount;

		std::unique_ptr<Window> m_window;
	};
}

