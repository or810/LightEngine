#pragma once

#include <memory>
#include <vector>
#include <optional>
#include "Engine/data/BinarySearchTree.h"
#include "ISystem.h"

namespace Light {
	template<typename T, typename Comparator = std::greater<uint32_t>>
	class IPrioritySequence {
	public:
		using Iterator = typename BinarySearchTree<T, Comparator>::Iterator;

		IPrioritySequence(Comparator comparator = Comparator())
			: m_tree(comparator) {
		}

		void insert(const T& element, uint32_t priority) { m_tree.insert(element, priority); }

		void remove(const T& element) { m_tree.remove(element); }

		Iterator begin() const { return m_tree.begin(); }

		Iterator end() const { return m_tree.end(); }

	protected:
		BinarySearchTree<T, Comparator> m_tree;
	};

	template<typename T>
	class PriorityQueue : IPrioritySequence<T, std::less<uint32_t>>
	{
	public:
		PriorityQueue() : m_count(0) {}

		void push(T& element) { insert(element, m_count++); }

		

		void pop(T& element) { 
			remove(element, m_count - 1); 
			m_count--; 
		}

		void operator<<(const T& element) { push(element); }
		void operator<<(T& element) { push(element); }

	private:
		uint32_t m_count;
	};
}

//
//namespace Light {
//	
//	template<typename T, typename Comparator = std::greater<uint32_t>>
//	class ISequenceManagementHandler {
//	protected:
//
//		ISequenceManagementHandler(Comparator comparator = Comparator())
//		{
//			m_tree = BinarySearchTree<T, Comparator>>(comparator);
//		}
//
//		void insert(T& element, uint32_t priority) { m_tree->insert(element, priority); }
//		
//		void remove(T& element) { m_tree->remove(element); }
//
//	protected:
//		BinarySearchTree<T, Comparator>& m_tree;
//	};
//
//	template<typename T>
//	class QueueSequenceStrategy : public ISequenceManagementHandler<T, std::greater<uint32_t>> {
//	protected:
//		QueueSequenceStrategy() : m_count(0) {
//			// Automatically use std::greater comparator for priority-based sorting
//			this->m_tree = std::make_unique<BinarySearchTree<T, std::greater<uint32_t>>>();
//		}
//
//		void put(T& element, uint32_t priority) {
//			this->m_tree->insert(element, priority);
//			++m_count;
//		}
//
//		void push(const std::shared_ptr<T>& element) {
//			this->put(element, m_count);
//		}
//
//	private:
//		uint32_t m_count;
//	};
//
//
//	class SystemManager : public QueueSequenceStrategy<ISystem> {
//	public:
//		void unregisterSystem(std::shared_ptr<ISystem>& system);
//		uint32_t getPriority(std::shared_ptr<ISystem>& system) const;
//		std::optional<uint32_t> tryGetPriority(std::shared_ptr<ISystem>& system) const;
//		uint32_t setPriority(std::shared_ptr<ISystem>& system, uint32_t newPriority);
//		void registerSystems(std::vector<std::shared_ptr<ISystem>>& systems, uint32_t priority);
//		void registerSystem(std::shared_ptr<ISystem>& system);
//
//		void registerSystem(std::shared_ptr<ISystem>& system, uint32_t priority) {
//
//		}
//
//
//	};
//}
//
//
