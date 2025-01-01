#include "pch.h"
#include "SystemManager.h"

void Light::SystemManager::registerSystems(const std::vector<std::shared_ptr<ISystem>>& systems, uint32_t priority) {
    for (const auto& system : systems) {
        registerSystem(system, priority);  // Register each system with a given priority
    }
}

void Light::SystemManager::unregisterSystems(const std::vector<std::shared_ptr<ISystem>>& systems) {
    for (const auto& system : systems) {
        unregisterSystem(system);  // Unregister each system
    }
}

void Light::SystemManager::registerSystem(std::shared_ptr<ISystem> system) {
    // Push the system into the queue with auto-generated priority (based on insertion order)
    this->push(system);
}

void Light::SystemManager::registerSystem(std::shared_ptr<ISystem> system, uint32_t priority) {
    // Insert system into the tree with the given priority
    insert(system, priority);
}

void Light::SystemManager::unregisterSystem(std::shared_ptr<ISystem> system) {
    // Remove system from the tree
    remove(system);
}

uint32_t Light::SystemManager::getPriority(std::shared_ptr<ISystem> system) {
    // Look for the system in the tree and return its priority
    auto node = this->m_tree->search(system);
    if (!node) {
        throw std::runtime_error("System not found");
    }
    return node->priority;
}

std::optional<uint32_t> Light::SystemManager::tryGetPriority(std::shared_ptr<ISystem> system) {
    // Look for the system and return its priority if found
    auto node = this->m_tree->search(system);
    if (!node) {
        return std::nullopt;  // Return an empty optional if not found
    }
    return node->priority;
}

uint32_t Light::SystemManager::setPriority(std::shared_ptr<ISystem> system, uint32_t newPriority) {
    // Find the system in the tree and update its priority if necessary
    auto node = this->m_tree->search(system);
    if (!node) {
        throw std::runtime_error("System not found");
    }

    // If priority is different, remove and re-insert the system with the new priority
    if (node->priority != newPriority) {
        this->m_tree->remove(system);
        this->m_tree->insert(system, newPriority);
    }
    return newPriority;
}

