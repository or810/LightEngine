#pragma once

#include <memory>
#include <unordered_map>
#include <cassert>
#include <typeindex>
#include "EntityManager.h"
#include "Signature.h"
#include "ComponentPool.h"

namespace Light {

	#define MAX_COMPONENTS 64

	using Component = std::uint32_t;

	class ComponentManager {
	public:

		ComponentManager() : 
			m_entitySignatures(), 
			m_indexToPool(),
			m_registeredComponents(), 
			m_registeredComponentsCounter(0) {}

		template<class T>
		void registerComponent() {
			std::type_index index = typeid(T);
			assert(m_indexToPool.find(index) != m_indexToPool.end());

			auto sharedComponentPool = std::make_shared<ComponentPool<T>>();
			m_registeredComponents[m_registeredComponentsCounter] = sharedComponentPool;
			m_indexToPool.insert(typeid(T), m_registeredComponentsCounter);

			m_registeredComponentsCounter++;
		}

		template<class T>
		T& getComponent(Entity entity)
		{
			// don't even worry about, it's all good.
			return getComponentPool<T>()->getComponent(entity);
		}

		std::shared_ptr<Signature> getEntitySignature(Entity& entity)
		{
			return m_entitySignatures[entity];
		}

		template<class T>
		void add(Entity entity, T& component) 
		{
			getComponentPool<T>()->insertComponent(entity, component);
			m_entitySignatures[entity]->addComponent<typeid(component)>();
		}

		template<class... T>
		void add(Entity entity, T&... components)
		{
			// Using fold expression to insert each component into its pool, and add it to the entity's signature.
			(getComponentPool<T>()->insertComponent(entity, components), ...);
			(m_entitySignatures[entity]->addComponent<typeid(components)>(), ...)
		}
	
	private:
		friend class ECSCoordinator;

		std::array<std::shared_ptr<Signature>, MAX_ENTITIES> m_entitySignatures;
		std::array<std::shared_ptr<IComponentPool>, MAX_COMPONENTS> m_registeredComponents;
		std::unordered_map<std::type_index, size_t> m_indexToPool;
		size_t m_registeredComponentsCounter = 0;
		
		template<class T>
		std::shared_ptr<ComponentPool<T>> getComponentPool() {
			return std::dynamic_pointer_cast<ComponentPool<T>>
				(m_registeredComponents[m_indexToPool[typeid(T)]]);
		}

	};

}


