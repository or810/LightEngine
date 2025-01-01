#pragma once

#include <memory>
#include <stack>
#include <stdexcept>
#include <functional>

namespace Light {

    // Node structure with support for shared_ptr elements
    template<typename T>
    struct Node {
        std::shared_ptr<T> element; // Use shared_ptr for polymorphic objects
        uint32_t priority;
        std::shared_ptr<Node<T>> left, right;

        Node(const std::shared_ptr<T>& e, uint32_t p) : element(e), priority(p), left(nullptr), right(nullptr) {}
    };

    // Binary Search Tree
    template<typename T, typename Comparator = std::greater<uint32_t>>
    class BinarySearchTree {
    public:
        using NodePtr = std::shared_ptr<Node<T>>;

        BinarySearchTree(Comparator comp = Comparator()) : root(nullptr), comparator(comp) {}

        void insert(const std::shared_ptr<T>& element, uint32_t priority) {
            root = insert(root, element, priority);
        }

        void remove(const std::shared_ptr<T>& element) {
            root = remove(root, element);
        }

        std::shared_ptr<T> search(const std::shared_ptr<T>& element) const {
            auto node = search(root, element);
            return node ? node->element : nullptr;
        }

        class Iterator;

        Iterator begin() const { return Iterator(root); }

        Iterator end() const { return Iterator(nullptr); }

    private:
        Comparator comparator;
        NodePtr root;

        NodePtr insert(NodePtr node, const std::shared_ptr<T>& element, uint32_t priority) {
            if (!node) return std::make_shared<Node<T>>(element, priority);
            if (comparator(priority, node->priority)) {
                node->left = insert(node->left, element, priority);
            }
            else {
                node->right = insert(node->right, element, priority);
            }
            return node;
        }

        NodePtr remove(NodePtr node, const std::shared_ptr<T>& element) {
            if (!node) return nullptr;

            if (*(node->element) == *element) { // Compare by dereferencing
                if (!node->left) return node->right;
                if (!node->right) return node->left;

                auto minNode = find_min(node->right);
                node->element = minNode->element;
                node->priority = minNode->priority;
                node->right = remove(node->right, minNode->element);
            }
            else if (comparator(node->priority, 0) && comparator(0, node->priority)) {
                node->left = remove(node->left, element);
            }
            else {
                node->right = remove(node->right, element);
            }
            return node;
        }

        NodePtr search(NodePtr node, const std::shared_ptr<T>& element) const {
            if (!node || *(node->element) == *element) return node;
            if (comparator(element->priority, node->priority)) {
                return search(node->left, element);
            }
            else {
                return search(node->right, element);
            }
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
            std::stack<NodePtr> stack;

            void pushLeft(NodePtr node) {
                while (node) {
                    stack.push(node);
                    node = node->left;
                }
            }

        public:
            Iterator(NodePtr root) { pushLeft(root); }

            uint32_t& priority() const {
                return stack.top()->priority; // Access priority of current node
            }


            T& operator*() {
                return *stack.top()->element; // Dereference shared_ptr to get value
            }

            T& operator*() const {
                return *stack.top()->element; // Dereference shared_ptr to get value
            }

            std::shared_ptr<T> operator->() const {
                return stack.top()->element; // Access shared_ptr directly
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
