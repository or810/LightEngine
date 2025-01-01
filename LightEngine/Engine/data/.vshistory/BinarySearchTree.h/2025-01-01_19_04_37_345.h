#pragma once

#include <memory>
#include <stack>
#include <stdexcept>
#include <functional>

namespace Light {

    template<typename T>
    struct Node {
        T& element;
        uint32_t priority;
        std::shared_ptr<Node<T>> left, right;

        Node(const T& e, uint32_t p) : element(e), priority(p), left(nullptr), right(nullptr) {}
    };

    template<typename T, typename Comparator = std::greater<uint32_t>>
    class BinarySearchTree {
    public:
        using NodePtr = std::shared_ptr<Node<T>>;

        BinarySearchTree(Comparator comp = Comparator()) : root(nullptr), comparator(comp) {}

        void insert(const T& element, uint32_t priority) {
            root = insert(root, element, priority);
        }

        void remove(const T& element) {
            root = remove(root, element);
        }

        NodePtr search(const T& element) const {
            return search(root, element);
        }

        NodePtr searchNode(const NodePtr& node) const {
            return find(root, node);
        }

        class Iterator;

        Iterator begin() const {
            return Iterator(root);
        }

        Iterator end() const {
            return Iterator(nullptr);
        }

    private:
        Comparator comparator;
        NodePtr root;

        NodePtr insert(NodePtr node, const T& element, uint32_t priority) {
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

        NodePtr remove(NodePtr node, const T& element) {
            if (!node) return nullptr;

            if (node->element == element) {
                if (!node->left) return node->right;
                if (!node->right) return node->left;

                NodePtr minNode = find_min(node->right);
                node->element = minNode->element;
                node->priority = minNode->priority;
                node->right = remove(node->right, minNode->element);
            }
            else if (comparator(node->priority, 0) && comparator(0, node->priority)) {  // Keep comparison valid
                node->left = remove(node->left, element);
            }
            else {
                node->right = remove(node->right, element);
            }
            return node;
        }

        NodePtr search(NodePtr node, const T& element) const {
            if (!node || node->element == element) {
                return node;
            }
            if (comparator(0, node->priority)) {
                return search(node->left, element);
            }
            else {
                return search(node->right, element);
            }
        }

        NodePtr find(NodePtr node, const NodePtr& target) const {
            if (!node) return nullptr;
            if (node == target) {
                return node;
            }
            auto found = find(node->left, target);
            return found ? found : find(node->right, target);
        }

        NodePtr find_min(NodePtr node) const {
            while (node && node->left) {
                node = node->left;
            }
            return node;
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
                return stack.top()->element;
            }

            T* operator->() const {
                return &(stack.top()->element);
            }
            
            uint32_t& priority() const {
                return stack.top()->priority; // Access priority of current node
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
                if (stack.empty() && other.stack.empty()) return false;
                if (stack.empty() || other.stack.empty()) return true;
                return stack.top() != other.stack.top();
            }
        };
    };
}
