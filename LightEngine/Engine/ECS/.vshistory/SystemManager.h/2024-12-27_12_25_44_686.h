#pragma once

#include <memory>
#include <vector>
#include <optional>
#include "Engine/data/BinarySearchTree.h"
#include "ISystem.h"

namespace Light {
	
	template<typename T>
	class ISequenceManagementHandler {
	protected:

		ISequenceManagementHandler() { m_tree = std::make_unique<BinarySearchTree<T>>(); }

		void insert(T& element, uint32_t priority) { m_tree->insert(element, priority); }
		
		void remove(T& element) { m_tree->remove(element); }

	protected:
		std::unique_ptr<BinarySearchTree<T>> m_tree;
	};

	template<typename T>
	class QueueSequenceStrategy : public ISequenceManagementHandler<T>
	{
	protected:
		QueueSequenceStrategy() : m_count(0) { }

		void put(T& element, uint32_t priority) {
			m_tree->insert(element, priority); 
			++m_count;
		}
		void push(T& element) { this->put(element, m_count); }

	private:
		uint32_t m_count;
	};
	class SystemManager : public QueueSequenceStrategy<std::shared_ptr<ISystem>> {
	public:
		void registerSystem(std::shared_ptr<ISystem> system);

		void registerSystem(std::shared_ptr<ISystem> system, uint32_t priority);

		void unregisterSystem(std::shared_ptr<ISystem> system);

		uint32_t getPriority(std::shared_ptr<ISystem> system);

		std::optional<uint32_t> tryGetPriority(std::shared_ptr<ISystem> system);

		uint32_t setPriority(std::shared_ptr<ISystem> system, uint32_t newPriority);

	};
}


