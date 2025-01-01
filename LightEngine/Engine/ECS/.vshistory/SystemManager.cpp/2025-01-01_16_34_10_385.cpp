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

void Light::SystemManager::registerSystem(const std::shared_ptr<ISystem>& system) {
    this->push(system);
}

void Light::SystemManager::registerSystem(const std::shared_ptr<ISystem>& system, uint32_t priority) {
    this->m_tree.insert(system, priority); // Use '.' for accessing BinarySearchTree
}

void Light::SystemManager::unregisterSystem(const std::shared_ptr<ISystem>& system) {
    remove(system);
}

uint32_t Light::SystemManager::getPriority(const std::shared_ptr<ISystem>& system) const {
    auto node = this->m_tree->search(system);
    if (!node) {
        throw std::runtime_error("System not found");
    }
    return node->priority;
}

std::optional<uint32_t> Light::SystemManager::tryGetPriority(const std::shared_ptr<ISystem>& system) const {
    auto node = this->m_tree->search(system);
    if (!node) {
        return std::nullopt;
    }
    return node->priority;
}

uint32_t Light::SystemManager::setPriority(const std::shared_ptr<ISystem>& system, uint32_t newPriority) {
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