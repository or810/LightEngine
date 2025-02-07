#pragma once

#include "Engine/EntityComponentSystem/Components/ComponentManager.h"
#include "Engine/EntityComponentSystem/Entities/EntityManager.h"

namespace Light {
	namespace ECS {
		
		class ComponentManager;
		class EntityManager;

		class EntityHandler {
		public:
			EntityHandler(Entity entity, ComponentManager& componentManager, EntityManager& entityManager)
				: m_entity(entity), m_componentManager(componentManager), m_entityManager(entityManager) { }

			template <typename T, typename... Args>
			void addComponent(Args&&... args) {
				componentManager.addComponent<T>(entity, T(std::forward<Args>(args)...));
			}

			template<typename T>
			void removeComponent()
			{
				m_componentManager.removeComponent<T>(m_entity);
			}

			template<typename T>
			T* getComponent() const
			{
				return m_componentManager.getComponent<T>(m_entity);
			}

			Entity getID() const
			{
				return m_entity;
			}

		private:
			ComponentManager& m_componentManager;
			EntityManager& m_entityManager;
			Entity m_entity;
		};
	}
}