#pragma once

#include <memory>
#include <vector>
#include <optional>
#include "Engine/data/BinarySearchTree.h"
#include "Engine/ECS/ISystem.h"

namespace Light {

    // Base class IPrioritySequence definition
    template<typename T, typename Comparator = std::greater<uint32_t>>
    class IPrioritySequence {
    public:
        using Iterator = typename BinarySearchTree<T, Comparator>::Iterator;

        IPrioritySequence(Comparator comparator = Comparator());

        void insert(const T& element, uint32_t priority);
        void remove(const T& element);

        Iterator begin() const;
        Iterator end() const;

    protected:
        BinarySearchTree<T, Comparator> m_tree;
    };

    // Derived class PriorityQueue definition
    template<typename T>
    class PriorityQueue : public IPrioritySequence<T, std::less<uint32_t>> {
    public:
        using Base = IPrioritySequence<T, std::less<uint32_t>>;
        using Iterator = typename Base::Iterator;

        PriorityQueue();

        void push(const T& element);
        void pop(T& element);

        PriorityQueue<T>& operator<<(const T& element);

        Iterator begin() const;
        Iterator end() const;

    private:
        uint32_t m_count;
    };

} // namespace Light