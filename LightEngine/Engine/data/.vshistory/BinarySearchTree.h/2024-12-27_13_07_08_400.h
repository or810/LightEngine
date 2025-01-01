#pragma once

#include <memory>
#include <stack>
#include <stdexcept>
#include <functional>

namespace Light {

    // Node struct that holds data and priority
    template<typename T>
    class Node {
    public:
        T data;               // The actual data
        uint32_t priority;    // Priority used for comparisons
        std::shared_ptr<Node<T>> left;
        std::shared_ptr<Node<T>> right;

        Node(const T& value, uint32_t priority)
            : data(value), priority(priority), left(nullptr), right(nullptr) {
        }
    };

    // BinarySearchTree comparing nodes based on the priority field
    template<typename T, typename Comparator = std::greater<uint32_t>>
    class BinarySearchTree {
    public:
        BinarySearchTree(Comparator comp = Comparator()) : m_root(nullptr), comp(comp) {}

        void insert(const T& x, uint32_t priority) {
            m_root = insert(x, priority, m_root);
        }

        void remove(const T& x) {
            m_root = remove(x, m_root);
        }

        uint32_t getPriority(std::shared_ptr<Node<T>> x) const {
            auto node = search(x);
            if (!node) {
                throw std::runtime_error("Element not found");
            }
            return node->priority;
        }

        std::shared_ptr<Node<T>> search(std::shared_ptr<Node<T>> x) const {
            return find(m_root, x);
        }

        class Iterator;

        Iterator begin() const {
            return Iterator(m_root);
        }

        Iterator end() const {
            return Iterator(nullptr);
        }

    private:
        Comparator comp;
        std::shared_ptr<Node<T>> m_root;

        // Find a node based on its priority
        std::shared_ptr<Node<T>> find(std::shared_ptr<Node<T>> t, const T& x) const {
            if (!t) return nullptr;
            if (comp(x.priority, t->priority)) {  // Compare based on node's priority
                return find(t->left, x);
            }
            else if (comp(t->priority, x.priority)) {  // Compare based on node's priority
                return find(t->right, x);
            }
            return t;
        }

        // Insert a new node with the given priority
        std::shared_ptr<Node<T>> insert(const T& x, uint32_t priority, std::shared_ptr<Node<T>> t) {
            if (!t) {
                return std::make_shared<Node<T>>(x, priority);
            }
            if (comp(priority, t->priority)) {
                t->left = insert(x, priority, t->left);  // Insert left if the priority is smaller
            }
            else if (comp(t->priority, priority)) {
                t->right = insert(x, priority, t->right); // Insert right if the priority is greater
            }
            return t;
        }

        // Remove a node based on its priority
        std::shared_ptr<Node<T>> remove(const T& x, std::shared_ptr<Node<T>> t) {
            if (!t) return nullptr;

            if (comp(x.priority, t->priority)) {
                t->left = remove(x, t->left);
            }
            else if (comp(t->priority, x.priority)) {
                t->right = remove(x, t->right);
            }
            else if (t->left && t->right) {
                auto minNode = findMin(t->right);
                t->data = minNode->data;
                t->priority = minNode->priority;
                t->right = remove(t->data, t->right);
            }
            else {
                return t->left ? t->left : t->right;
            }
            return t;
        }

        // Find the minimum node (with the lowest priority)
        std::shared_ptr<Node<T>> findMin(std::shared_ptr<Node<T>> t) const {
            if (!t) return nullptr;
            while (t->left) {
                t = t->left;
            }
            return t;
        }

        // Iterator Class
        class Iterator {
        private:
            std::stack<std::shared_ptr<Node<T>>> stack;

            // Push nodes down the left subtree
            void pushLeft(std::shared_ptr<Node<T>> node) {
                while (node) {
                    stack.push(node);
                    node = node->left;
                }
            }

        public:
            Iterator(std::shared_ptr<Node<T>> root) {
                pushLeft(root);
            }

            T& operator*() const {
                return stack.top()->data;
            }

            T* operator->() const {
                return &(stack.top()->data);
            }

            Iterator& operator++() {
                auto node = stack.top();
                stack.pop();
                if (node->right) {
                    pushLeft(node->right);
                }
                return *this;
            }

            bool operator!=(const Iterator& other) const {
                return stack.top() != other.stack.top();
            }
        };
    };

}
