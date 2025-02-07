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
