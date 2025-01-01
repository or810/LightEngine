#include "pch.h"



#include "SystemManager.h"
void Light::SystemManager::registerSystem(std::shared_ptr<ISystem> system) {
	push(system);
}

void Light::SystemManager::registerSystem(std::shared_ptr<ISystem> system, uint32_t priority) {
	insert(system, priority);
}

void Light::SystemManager::unregisterSystem(std::shared_ptr<ISystem> system) {
	remove(system);
}

uint32_t Light::SystemManager::getPriority(std::shared_ptr<Node<ISystem>> system) {
	auto node = this->m_tree->search(system);
	if (!node) {
		throw std::runtime_error("System not found");
	}
	return node->priority;
}

std::optional<uint32_t> Light::SystemManager::tryGetPriority(std::shared_ptr<Node<ISystem>> system) {
	auto node = this->m_tree->search(system);
	if (!node) {
		return std::nullopt; // Return an empty optional if not found
	}
	return node->priority;
}

uint32_t Light::SystemManager::setPriority(std::shared_ptr<Node<ISystem>> system, uint32_t newPriority) {
	// Find the system node in the tree
	auto node = this->m_tree->search(system);
	if (!node) {
		throw std::runtime_error("System not found");
	}

	// Check if the priority is actually changing
	if (node->priority == newPriority) {
		return newPriority; // No change needed
	}

	// Remove the node with the old priority
	this->m_tree->remove(system);

	// Reinsert the node with the new priority
	this->m_tree->insert(system, newPriority);

	return newPriority;
}
