#pragma once

#include "Engine/EntityComponentSystem/Components/ComponentPool.h"
#include "Engine/EntityComponentSystem/Signature.h"
#include "unordered_map"
#include <Allocator.h>

namespace Light {
	namespace ECS {

		class ComponentManager {
		public:
			ComponentManager(size_t initialPoolSize)
				: allocator(initialPoolSize), m_initialPoolSize(initialPoolSize) { }

			~ComponentManager() {
				for (auto& [id, pool] : componentPools) {
					delete static_cast<ComponentPoolBase*>(pool);
				}
			}

			template <typename T>
			void registerComponent() {
				const ComponentID id = SignatureManager::getComponentID<T>();
				if (componentPools.find(id) == componentPools.end()) {
					auto* pool = allocator.allocateObject<ComponentPool<T>>(m_initialPoolSize);
					assert(pool != nullptr && "ComponentPool allocation failed");
					componentPools[id] = pool;
				}
			}

			template <typename T>
			void addComponent(Entity entity, T component) {
				getComponentPool<T>()->add(entity, std::move(component));
			}

			template <typename T>
			void removeComponent(Entity entity) {
				getComponentPool<T>()->remove(entity);
			}

			template <typename T>
			T* getComponent(Entity entity) {
				return getComponentPool<T>()->get(entity);
			}


		private:
			Allocator allocator;
			size_t m_initialPoolSize;
			std::unordered_map<ComponentID, void*> componentPools;

			template<typename C>
			ComponentPool<C>* getComponentPool()
			{
				const ComponentID id = SignatureManager::getComponentID<C>();
				auto it = componentPools.find(id);

				return (it != componentPools.end()) ?
					static_cast<ComponentPool<C>*>(it->second) : nullptr;
			}
		};
	}
}
