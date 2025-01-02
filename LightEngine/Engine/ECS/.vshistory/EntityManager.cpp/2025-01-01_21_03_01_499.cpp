#include "pch.h"
#include "EntityManager.h"


const Light::Entity& Light::EntityManager::CreateEntity()
{
	assert(m_entitiesAlive < MAX_ENTITIES);
	Entity& temp = m_entitiesAlive;
	m_entities[m_entitiesAlive++] = temp;
	return temp;
}

void Light::EntityManager::deleteEntity(Entity entity) {
	assert(entity < m_entitiesAlive);
	m_entities[entity] = m_entities.back();

}