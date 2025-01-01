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

std::optional<uint32_t> Light::SystemManager::tryGetPriority(ISystem& system)
{
	auto it = m_systems.get(system);

	if (it.has_value())
		return it.value().priority();
	return {};
}

bool Light::SystemManager::setPriority(ISystem& system, uint32_t newPriority)
{
	auto it = m_systems.get(system);

	if (!it.has_value())
		return false;
	it.value().priority() = newPriority;
	return true;
}

void Light::SystemManager::updateAll(EntitiesArray entities, DeltaTime dt)
{
	for (auto it = m_systems.begin(); it != m_systems.end(); ++it)
		it->update(entities);
}
