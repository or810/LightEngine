#pragma once

#include <memory>
#include <stack>
#include <stdexcept>
#include <functional>

namespace Light {

    // Node struct that holds data and priority
    template<typename T>
    struct Node {
        T element;    // Element (std::shared_ptr<ISystem>)
        uint32_t priority;  // Priority of the element
        std::shared_ptr<Node<T>> left, right;

        Node(T e, uint32_t p) : element(e), priority(p), left(nullptr), right(nullptr) {}
    };

    // BinarySearchTree comparing nodes based on the priority field
    template<typename T, typename Comparator = std::greater<uint32_t>>
    class BinarySearchTree {
    public:

        using NodePtr = std::shared_ptr<Node<T>>;

        BinarySearchTree(Comparator comp = Comparator()) : m_root(nullptr), comparator(comparator) {}

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
        Comparator comparator;
        NodePtr root;

        NodePtr insert(NodePtr node, T element, uint32_t priority) {
            if (!node) {
                return std::make_shared<Node<T>>(element, priority);
            }

            if (comparator(priority, node->priority)) {
                node->left = insert(node->left, element, priority);
            }
            else {
                node->right = insert(node->right, element, priority);
            }
            return node;
        }

        NodePtr search(NodePtr node, T element) const {
            if (!node) return nullptr;
            if (node->element == element) {
                return node;
            }
            if (comparator(element->priority, node->priority)) {
                return search(node->left, element);
            }
            else {
                return search(node->right, element);
            }
        }

        NodePtr remove(NodePtr node, T element) {
            if (!node) return nullptr;

            if (node->element == element) {
                if (!node->left) return node->right;
                if (!node->right) return node->left;

                NodePtr minNode = find_min(node->right);
                node->element = minNode->element;
                node->priority = minNode->priority;
                node->right = remove(node->right, minNode->element);
            }
            else if (comparator(element->priority, node->priority)) {
                node->left = remove(node->left, element);
            }
            else {
                node->right = remove(node->right, element);
            }

            return node;
        }

        NodePtr find_min(NodePtr node) {
            while (node->left) {
                node = node->left;
            }
            return node;
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
