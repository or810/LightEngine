#pragma once

#include "Engine/EntityComponentSystem/Components/ComponentManager.h"
#include "Engine/EntityComponentSystem/Entities/EntityManager.h"

namespace Light {
	namespace ECS {
		
		class EntityHandler {
		public:
			EntityHandler(Entity entity, ComponentManager& componentManager, EntityManager& entityManager)
				: entity(entity), componentManager(componentManager), entityManager(entityManager) { }

			template<typename T, typename... Cs>
			void addComponent(Cs&&... args)
			{
				componentManager.addComponent<T>(entity, T(std::forward<Cs>(args) ...));
			}

			template<typename T>
			void removeComponent()
			{
				componentManager.removeComponent<T>(entity);
			}

			template<typename T>
			T* getComponent() const
			{
				return componentManager.getComponent<T>(entity);
			}

			Entity getID() const
			{
				return entity;
			}

		private:
			ComponentManager& componentManager;
			EntityManager& entityManager;
			Entity entity;
		};
	}
}