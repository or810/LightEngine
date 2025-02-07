#pragma once

#include "../scenary/Camera.h"
#include "SFML/Graphics.hpp"

namespace Light {
	class SFMLCamera : public Camera
	{
	public:
		SFMLCamera(PositionComponent& position, Rectangle& windowRect);

		sf::View& getView();
	private:
		sf::View m_viewport;
	};

}

