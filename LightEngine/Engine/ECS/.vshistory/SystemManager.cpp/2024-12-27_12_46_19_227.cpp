#include "pch.h"
#include "SystemManager.h"

void Light::SystemManager::registerSystems(const std::vector<std::shared_ptr<ISystem>>& systems, uint32_t priority) {
	for (const auto& system : systems) {
		registerSystem(system, priority);
	}
}

void Light::SystemManager::unregisterSystems(const std::vector<std::shared_ptr<ISystem>>& systems) {
	for (const auto& system : systems) {
		unregisterSystem(system);
	}
}

void Light::SystemManager::registerSystem(std::shared_ptr<ISystem> system) {
	this->push(system);
}

void Light::SystemManager::registerSystem(std::shared_ptr<ISystem> system, uint32_t priority) {
	insert(system, priority);
}

void Light::SystemManager::unregisterSystem(std::shared_ptr<ISystem> system) {
	remove(system);
}

uint32_t Light::SystemManager::getPriority(std::shared_ptr<ISystem> system) {
	auto node = this->m_tree->search(system);
	if (!node) {
		throw std::runtime_error("System not found");
	}
	return node->priority;
}

std::optional<uint32_t> Light::SystemManager::tryGetPriority(std::shared_ptr<ISystem> system) {
	auto node = this->m_tree->search(system);
	if (!node) {
		return std::nullopt; // Return an empty optional if not found
	}
	return node->priority;
}

uint32_t Light::SystemManager::setPriority(std::shared_ptr<ISystem> system, uint32_t newPriority) {
	auto node = this->m_tree->search(system);
	if (!node) {
		throw std::runtime_error("System not found");
	}

	if (node->priority != newPriority) {
		this->m_tree->remove(system);
		this->m_tree->insert(system, newPriority);
	}
	return newPriority;
}
