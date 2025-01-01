#pragma once

#include <memory>
#include <vector>
#include <optional>
#include "Engine/data/BinarySearchTree.h"
#include "Engine/ECS/ISystem.h"

namespace Light {

	template<typename T, typename Comparator = std::greater<uint32_t>>
	class IPrioritySequence {
	public:
		using Iterator = typename BinarySearchTree<T, Comparator>::Iterator;

		IPrioritySequence(Comparator comparator = Comparator())
			: m_tree(comparator) {
		}

		void insert(std::shared_ptr<T> element, uint32_t priority) {
			m_tree.insert(element, priority);
		}
		
		void removeElement(std::shared_ptr<T> element) {
			m_tree.remove(element);
		}

		Iterator begin() const { return m_tree.begin(); }

		Iterator end() const { return m_tree.end(); }

	protected:
		BinarySearchTree<T, Comparator> m_tree;
	};

	template<typename T>
	class PriorityQueue : public IPrioritySequence<T, std::less<uint32_t>> {
	public:
		using Base = IPrioritySequence<T, std::less<uint32_t>>;
		using Iterator = typename Base::Iterator;

		PriorityQueue() : m_count(0) {}

		void push(std::shared_ptr<T> element) {
			this->insert(element, m_count++);
		}

		void pop(std::shared_ptr<T> element) {
			this->remove(element);
			m_count--;
		}

		PriorityQueue<T>& operator<<(const T& element) {
			auto sharedPtr = std::make_shared<T>(element);
			push(sharedPtr);
			return *this;
		}

		PriorityQueue<T>& operator<<(const std::shared_ptr<T> element) {
			push(element);
			return *this;
		}

		void remove(const std::shared_ptr<T> element) {
			this->removeElement(element);
		}

		Iterator begin() const { return Base::begin(); }

		Iterator end() const { return Base::end(); }

	private:
		uint32_t m_count;
	};
}