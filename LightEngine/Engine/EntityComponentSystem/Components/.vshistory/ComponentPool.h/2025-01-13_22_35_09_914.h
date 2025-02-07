#pragma once
#include <cstdint>
#include <vector>

namespace Light {
	namespace ECS {

		using Entity = uint32_t;

		template<typename C>
		class ComponentPool {
		public:
			explicit ComponentPool(size_t poolSize) :
				data(poolSize),
				entityToIndex(poolSize, -1),
				indexToEntity(poolSize, -1),
				size(0) {
				assert(poolSize > 0 && "Pool size must be greater than 0");
			}

			void add(Entity entity, C Component)
			{
				assert(entity < data.size() && "Entity Out of range");
				if (entityToIndex[entity] != -1)
					return;

				size_t index = size++;
				entityToIndex[entity] = index;
				indexToEntity[index] = entity;
			}

			void remove(Entity entity)
			{
				assert(entity < data.size() && "Entity out of range");
				size_t index = entityToIndex[entity];
				if (index == -1)
					return;

				size_t lastIndex = --size;
				Entity lastEntity = indexToEntity[lastIndex];
				data[index] = std::move(data[lastIndex]);
				entityToIndex[lastEntity] = index;
				indexToEntity[index] = lastEntity;

				entityToIndex[entity] = -1;
				indexToEntity[lastIndex] = -1;
			}

			C* get(Entity entity)
			{
				size_t index = entityToIndex[entity];
				return (index != -1) ? &data[index] : nullptr;
			}

		private:
			std::vector<C> data;
			std::vector<int> entityToIndex;
			std::vector<int> indexToEntity;
			size_t size;
		};
	}
}
