#pragma once

#include <array>
#include <cstdlib>
#include <queue>
#include <cassert>

namespace Light {
#define MAX_ENTITIES 128
	using Entity = std::uint32_t;
	using EntitiesArray = std::array<Entity, MAX_ENTITIES>;

	//using EntityID std::uint32_t;

	class EntityManager
	{
	public:
		EntityManager() : m_entitiesAlive(0) { m_entities = { {} }; }
		const Entity CreateEntity()
		{
			assert(MAX_ENTITIES >= m_entitiesAlive);
			return Entity(m_entitiesAlive++);
		}

		void deleteEntity(Entity entity);

	private:
		std::array<Entity, MAX_ENTITIES> m_entities;
		std::uint32_t m_entitiesAlive;
	};

}
