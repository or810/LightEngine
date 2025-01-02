#pragma once

#include "SystemManager.h"
#include "EntityManager.h"
#include "ComponentManager.h"

namespace Light {
	class ECSCoordinator
	{
	public:
		ECSCoordinator()
		{
			m_systemManager = std::make_shared<SystemManager>();

		}

	private:
		std::shared_ptr<SystemManager> m_systemManager;
		std::shared_ptr<EntityManager> m_entityManager;
		std::shared_ptr<ComponentManager> m_componentManager;
	};
}
