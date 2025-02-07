#pragma once

#include "Engine/EntityComponentSystem/Allocator.h"
#include "Engine/EntityComponentSystem/Components/ComponentPool.h"
#include "Engine/EntityComponentSystem/Signature.h"
#include "unordered_map"

namespace Light {
	namespace ECS {

		class ComponentManager {
		public:
			ComponentManager(size_t initialPoolSize) : allocator(initialPoolSize) {}

			
			template <typename T>
			void registerComponent() {
				const ComponentID id = SignatureManager::GetComponentID<T>();
				if (componentPools.find(id) == componentPools.end()) {
					componentPools[id] = allocator.allocateObject<Core::ComponentPool<T>>(initialPoolSize);
				}
			}

			template <typename T>
			void addComponent(Entity entity, T component) {
				getComponentPool<T>()->add(entity, std::move(component));
			}

			template <typename T>
			void removeComponent(Entity entity) {
				getComponentPool<T>()->gemove(entity);
			}

			template <typename T>
			T* getComponent(Entity entity) {
				return getComponentPool<T>()->get(entity);
			}


		private:
			Allocator allocator;
			size_t initialPoolSize;
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
