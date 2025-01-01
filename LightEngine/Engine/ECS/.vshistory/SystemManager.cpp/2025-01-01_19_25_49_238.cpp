#include "pch.h"
#include "SystemManager.h"

void Light::SystemManager::registerSystem(std::shared_ptr<ISystem> system)
{
	m_systems.push(system);
}

void Light::SystemManager::unregisterSystem(std::shared_ptr<ISystem> system)
{
	m_systems.remove(system);
}

uint32_t Light::SystemManager::tryGetPriority(std::shared_ptr<ISystem> system)
{
	for (auto it = m_systems.begin(); it != m_systems.end(); ++it)
		if (*it == system)
			return it.priority();
	return NULL;
}

bool Light::SystemManager::setPriority(std::shared_ptr<ISystem> system, uint32_t newPriority) {
	for (auto it = m_systems.begin(); it != m_systems.end(); ++it) {
		if (*(*it) == *system) { // Dereference and compare
			it.priority() = newPriority;
			return true;
		}
	}
	return false;
}

void Light::SystemManager::updateAll(EntitiesArray entities, DeltaTime dt)
{
	for (auto it = m_systems.begin(); it != m_systems.end(); ++it)
		it->update(entities);
}
