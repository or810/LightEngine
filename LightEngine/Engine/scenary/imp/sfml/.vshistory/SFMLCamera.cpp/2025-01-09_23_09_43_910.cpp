#include "pch.h"
#include "SFMLCamera.h"

Light::SFMLCamera::SFMLCamera(PositionComponent& position, Rectangle& windowRect)
	: Camera(position, windowRect), m_viewport(sf::FloatRect(m_position.get().x, m_position.get().y, m_windowDimensions.width, m_windowDimensions.height))
{

}

sf::View& Light::SFMLCamera::getView() 
{
	return m_viewport;
}
