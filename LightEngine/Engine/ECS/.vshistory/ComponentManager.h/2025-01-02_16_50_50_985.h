#pragma once

#include <memory>
#include <unordered_map>
#include <cassert>
#include <typeindex>
#include <type_traits>
#include "EntityManager.h"
#include "ComponentPool.h"
#include "Signature.h"

namespace Light {
	using Component = std::uint32_t;
	
	class ComponentManager {
	public:
		ComponentManager() :
			m_entitySignatures(), 
			m_indexToPool(),
			m_registeredComponents(),
			m_registeredComponentsCounter(0) {}

		template<typename Component>
		void registerComponent()
		{
			std::type_index index(typeid(Component));
			assert(m_indexToPool.find(index) != m_indexToPool.end());

			auto sharedComponentPool = std::make_shared<ComponentPool<Component>>();
			m_registeredComponents[m_registeredComponentsCounter] = sharedComponentPool;
			m_indexToPool.insert(index, m_registeredComponentsCounter);

			m_registeredComponentsCounter++;
		}

		template<typename Component>
		Component& getComponent(Entity& entity)
		{
			return getComponentPool<Component>()->getComponent<Component>(entity);
		}

		template<typename Component>
		Signature& getEntitySignature(Entity& entity)
		{
			return m_entitySignatures.at(entity);
		}

		template<typename Component>
		void add(Entity& entity, Component component)
		{
			getComponentPool<Component>()->insertComponent(entity, component);
			m_entitySignatures[entity].addComponent<Component>();
		}

		template<typename... Components>
		void add(Entity& entity, Components... components)
		{
			(getComponentPool<Components>()->insertComponent(entity, components), ...);
			(m_entitySignatures[entity].addComponent<Components>(), ...);
		}

	private:

		std::array<Signature, MAX_ENTITIES> m_entitySignatures;
		std::array<std::shared_ptr<IComponentPool>, MAX_COMPONENTS> m_registeredComponents;
		std::unordered_map<std::type_index, size_t> m_indexToPool;
		size_t m_registeredComponentsCounter;


		template<typename Component>
		std::shared_ptr<ComponentPool<Component>> getComponentPool()
		{
			return std::dynamic_pointer_cast<ComponentPool<Component>>
				(m_registeredComponents[m_indexToPool[std::type_index(typeid(Component))]]);
		}
	};
}


/*
namespace Light {

	using Component = std::uint32_t;

	class ComponentManager {
	public:

		ComponentManager() : 
			//m_entitySignatures(), 
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

		Signature& getEntitySignature(Entity& entity)
		{
			return m_entitySignatures.at(entity);
		}

		template<class T>
		void add(Entity entity, T& component) 
		{
			getComponentPool<T>()->insertComponent(entity, component);
			//m_entitySignatures.at(entity).addComponent<T>();
			Signature& signature = m_entitySignatures.at(entity);
			signature.addComponent<T>();
		}

		template<class... T>
		void add(Entity entity, T&... components)
		{
			// Using fold expression to insert each component into its pool, and add it to the entity's signature.
			(getComponentPool<T>()->insertComponent(entity, components), ...);
			//std::shared_ptr<Signature> signature = std::make_shared<Signature>();
			//Signature& sig;
			//sig.addComponents<T...>();
			//// Add the signature to the entity's map.
			//m_entitySignatures[entity] = signature;
		}
	
	private:
		friend class ECSCoordinator;

		std::array<Signature, MAX_ENTITIES> m_entitySignatures;
		std::array<std::shared_ptr<IComponentPool>, MAX_COMPONENTS> m_registeredComponents;
		std::unordered_map<std::type_index, size_t> m_indexToPool;
		size_t m_registeredComponentsCounter = 0;
		
		template<class T>
		std::shared_ptr<ComponentPool<T>> getComponentPool() {
			return std::dynamic_pointer_cast<ComponentPool<T>>
				(m_registeredComponents[m_indexToPool[typeid(T)]]);
		}
		
		// Updates the entity's signature
		void updateEntitySignature(Entity entity)
		{
			//std::shared_ptr<Signature> signature = std::make_shared<Signature>();
			//// Traverse through all registered component types and update signature for the entity
			/////*for (auto& [type, poolIndex] : m_indexToPool) {
			//	signature->addComponent(poolIndex);
			//}*/
			//signature->addComponent(typeid(PositionComponent)));
			//m_entitySignatures[entity] = signature;
//	
//	
//
//
//
//
//*/
