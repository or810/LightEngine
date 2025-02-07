#pragma once
#include <cstdint>
#include <queue>
#include <cassert>


namespace Light {
	namespace ECS {
		using Entity = uint32_t;
		constexpr Entity MAX_ENTITIES = 5000;

		class EntityManager {
		public:
			EntityManager() 
			{
				for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
					availableEntities.push(entity);
			}

			Entity createEntity()
			{
				assert(livingEntityCount < MAX_ENTITIES && "Too many entities");
				Entity id = availableEntities.front();
				availableEntities.pop();
				++livingEntityCount;
				return id;
			}

			Entity destroyEntity(Entity entity) {
				assert(entity < MAX_ENTITIES && "Entity out of range.");
				availableEntities.push(entity);
				--livingEntityCount;
			}

		private:
			std::queue<Entity> availableEntities;
			size_t livingEntityCount = 0;
		};
	}
}
