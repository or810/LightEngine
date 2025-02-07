#pragma once

#include "Engine/EntityComponentSystem/Components/ComponentManager.h"
#include "Engine/EntityComponentSystem/Entities/EntityManager.h"
#include "Engine/EntityComponentSystem/Entities/EntityHandler.h"
#include "Engine/EntityComponentSystem/Systems/SystemManager.h"


namespace Light {
	namespace ECS {

		class ECSCoordinator {
		public:
			ECSCoordinator()
				: componentManager(1024), entityManager(), systemManager() { }

			Entity createEntity() 
			{
				return entityManager.createEntity();
			}

			void destroyEntity(Entity entity)
			{
				entityManager.destroyEntity(entity);
			}

			EntityHandler getEntityHandler(Entity entity)
			{
				return { entity, componentManager, entityManager };
			}

			template<typename T, typename... Cs>
			T* registerSystem(Cs&&... args)
			{
				return systemManager.registerSystem<T>(std::forward<Cs>(args)...);
			}

			void updateSystems(float deltaTime)
			{
				systemManager.updateSystems(deltaTime);
			}

			template<typename... Cs>
			void registerComponent()
			{
				componentManager.registerComponents<Cs>();
			}

		private:
			ComponentManager componentManager;
			EntityManager entityManager;
			SystemManager systemManager;
		};
	}
}
