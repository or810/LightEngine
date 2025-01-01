#pragma once

namespace Light {
	/*
	* Represents a Pool of all the Entitiy's components that are of Type T
	*/
	template<class T>
	class ComponentPool : IComponentPool
	{
	public:
		void insertComponent(Entity entity, T component)
		{
			assert(m_components.find(entity) != m_components.end());
			m_components[entity] = component;
		}

		void removeComponent(Entity entity, T component)
		{
			assert(m_components.find(entity) == m_components.end());
			m_components.erase(entity);
		}

		template<class T>
		T& getComponent(Entity entity)
		{
			return m_components.at(entity);
		}

	private:
		std::unordered_map<Entity, T> m_components;
	};

}
