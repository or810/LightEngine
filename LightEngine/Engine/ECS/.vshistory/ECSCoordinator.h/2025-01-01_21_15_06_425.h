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
			m_entityManager = std::make_shared<EntityManager>();
			m_componentManager = std::make_shared<ComponentManager>();
		}

		const Entity& createEntity() {
			return m_entityManager->CreateEntity();
		}

		void deleteEntity(Entity& entity) 
		{
			m_entityManager->deleteEntity(entity);
			for(m_componentManager->m)
		}



	private:
		std::shared_ptr<SystemManager> m_systemManager;
		std::shared_ptr<EntityManager> m_entityManager;
		std::shared_ptr<ComponentManager> m_componentManager;
	};
}
