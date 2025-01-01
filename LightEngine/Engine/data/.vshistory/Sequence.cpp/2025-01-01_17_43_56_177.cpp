#include "pch.h"
#include "Sequence.h"

namespace Light {

    // IPrioritySequence constructor implementation
    template<typename T, typename Comparator>
    IPrioritySequence<T, Comparator>::IPrioritySequence(Comparator comparator)
        : m_tree(comparator) {
    }

    // insert method
    template<typename T, typename Comparator>
    void IPrioritySequence<T, Comparator>::insert(const T& element, uint32_t priority) {
        m_tree.insert(element, priority);
    }

    // remove method
    template<typename T, typename Comparator>
    void IPrioritySequence<T, Comparator>::remove(const T& element) {
        m_tree.remove(element);
    }

    // begin method
    template<typename T, typename Comparator>
    typename IPrioritySequence<T, Comparator>::Iterator
        IPrioritySequence<T, Comparator>::begin() const {
        return m_tree.begin();
    }

    // end method
    template<typename T, typename Comparator>
    typename IPrioritySequence<T, Comparator>::Iterator
        IPrioritySequence<T, Comparator>::end() const {
        return m_tree.end();
    }

    // PriorityQueue constructor
    template<typename T>
    PriorityQueue<T>::PriorityQueue() : m_count(0) {}

    // push method
    template<typename T>
    void PriorityQueue<T>::push(const T& element) {
        this->insert(element, m_count++);
    }

    // pop method
    template<typename T>
    void PriorityQueue<T>::pop(T& element) {
        this->remove(element);
        m_count--;
    }

    // operator<< method
    template<typename T>
    PriorityQueue<T>& PriorityQueue<T>::operator<<(const T& element) {
        push(element);
        return *this;
    }

    // begin method
    template<typename T>
    typename PriorityQueue<T>::Iterator
        PriorityQueue<T>::begin() const {
        return this->Base::begin();
    }

    // end method
    template<typename T>
    typename PriorityQueue<T>::Iterator
        PriorityQueue<T>::end() const {
        return this->Base::end();
    }

} // namespace Light
