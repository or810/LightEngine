#pragma once

#include <memory>
#include <vector>
#include <optional>
#include "Engine/data/BinarySearchTree.h"
#include "ISystem.h"

namespace Light {
	
	template<typename T, typename Comparator = std::greater<uint32_t>>
	class ISequenceManagementHandler {
	protected:

		ISequenceManagementHandler(Comparator comparator = Comparator())
		{
			m_tree = BinarySearchTree<T, Comparator>>(comparator);
		}

		void insert(T& element, uint32_t priority) { m_tree->insert(element, priority); }
		
		void remove(T& element) { m_tree->remove(element); }

	protected:
		BinarySearchTree<T, Comparator>& m_tree;
	};

	template<typename T>
	class QueueSequenceStrategy : public ISequenceManagementHandler<T, std::greater<uint32_t>> {
	protected:
		QueueSequenceStrategy() : m_count(0) {
			// Automatically use std::greater comparator for priority-based sorting
			this->m_tree = std::make_unique<BinarySearchTree<T, std::greater<uint32_t>>>();
		}

		void put(T& element, uint32_t priority) {
			this->m_tree->insert(element, priority);
			++m_count;
		}

		void push(T& element) {
			this->put(element, m_count);
		}

	private:
		uint32_t m_count;
	};


	class SystemManager : public QueueSequenceStrategy<std::shared_ptr<ISystem>> {
	public:
		void unregisterSystem(const std::shared_ptr<ISystem>& system);
		uint32_t getPriority(const std::shared_ptr<ISystem>& system) const;
		std::optional<uint32_t> tryGetPriority(const std::shared_ptr<ISystem>& system) const;
		uint32_t setPriority(const std::shared_ptr<ISystem>& system, uint32_t newPriority);
		void registerSystem(const std::shared_ptr<ISystem>& system);

		void registerSystem(const std::shared_ptr<ISystem>& system, uint32_t priority);














		void registerSystems(const std::vector<std::shared_ptr<ISystem>>& systems, uint32_t priority);

		void unregisterSystems(const std::vector<std::shared_ptr<ISystem>>& systems);



		//void registerSystem(std::shared_ptr<ISystem> system);

		//void registerSystem(std::shared_ptr<ISystem> system, uint32_t priority);

		//void unregisterSystem(std::shared_ptr<ISystem> system);

		uint32_t getPriority(std::shared_ptr<ISystem> system);

		std::optional<uint32_t> tryGetPriority(std::shared_ptr<ISystem> system);

		uint32_t setPriority(std::shared_ptr<Node<ISystem>> system, uint32_t newPriority);

	};
}


