#include "pch.h"
#include "SystemManager.h"

void Light::SystemManager::registerSystem(ISystem& system)
{
	m_systems << system;
}

void Light::SystemManager::unregisterSystem(ISystem& system)
{
	m_systems.remove(system);
}

uint32_t Light::SystemManager::tryGetPriority(ISystem& system)
{
	for (auto it = m_systems.begin(); it != m_systems.end(); ++it)
		if (*it == system)
			return it.priority();
	return NULL;
}

bool Light::SystemManager::setPriority(ISystem& system, uint32_t newPriority)
{
	for (auto it = m_systems.begin(); it != m_systems.end(); ++it)
		if (*it == system) {
			it.priority() = newPriority;
			return true;
		}
	return false;
}

void Light::SystemManager::updateAll(EntitiesArray entities, DeltaTime dt)
{
	for (auto it = m_systems.begin(); it != m_systems.end(); ++it)
		it->update(entities);
}
