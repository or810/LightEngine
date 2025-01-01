#pragma once

#include <memory>
#include <stack>
#include <stdexcept>

namespace Light {
    template<typename T, typename Comparator = std::less<T>>
    class Node {
    public:
        T data;
        uint32_t priority;  // Changed from reference to value
        std::shared_ptr<Node<T>> left;
        std::shared_ptr<Node<T>> right;

        Node(const T& value, uint32_t priority)
            : data(value), priority(priority), left(nullptr), right(nullptr) {
        }
    };

    template<typename T>
    class BinarySearchTree {
    public:
        BinarySearchTree() : m_root(nullptr) {}

        ~BinarySearchTree() {}

        void insert(const T& x, uint32_t priority) {
            m_root = insert(x, priority, m_root);
        }

        void remove(const T& x) {
            m_root = remove(x, m_root);
        }

        uint32_t getPriority(const T& x) const {
            auto node = search(x);
            if (!node) {
                throw std::runtime_error("Element not found");
            }
            return node->priority;
        }

        std::shared_ptr<Node<T>> search(const T& x) const {
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

        std::shared_ptr<Node<T>> find(std::shared_ptr<Node<T>> t, const T& x) const {
            if (!t) return nullptr;
            if (comp(x, t->data)) {
                return find(t->left, x);
            }
            else if (comp(t->data, x)) {
                return find(t->right, x);
            }
            return t;
        }

        std::shared_ptr<Node<T>> insert(const T& x, uint32_t priority, std::shared_ptr<Node<T>> t) {
            if (!t) {
                return std::make_shared<Node<T>>(x, priority);
            }
            if (comp(x, t->data)) {
                t->left = insert(x, priority, t->left);
            }
            else if (comp(t->data, x)) {
                t->right = insert(x, priority, t->right);
            }
            return t;
        }

        std::shared_ptr<Node<T>> remove(const T& x, std::shared_ptr<Node<T>> t) {
            if (!t) return nullptr; // Check for null before accessing t->data

            if (comp(x, t->data)) {
                t->left = remove(x, t->left); // Use comparator for x < t->data
            }
            else if (comp(t->data, x)) {
                t->right = remove(x, t->right); // Use comparator for x > t->data
            }
            else if (t->left && t->right) {
                auto minNode = findMin(t->right); // Find minimum in the right subtree
                t->data = minNode->data;         // Replace data with minimum
                t->priority = minNode->priority;
                t->right = remove(t->data, t->right); // Remove the minimum node
            }
            else {
                return t->left ? t->left : t->right; // Return the non-null child, if any
            }
            return t;
        }

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
                if (stack.empty() && other.stack.empty()) {
                    return false;
                }
                if (stack.empty() || other.stack.empty()) {
                    return true;
                }
                return stack.top() != other.stack.top();
            }
        };
    };
}
