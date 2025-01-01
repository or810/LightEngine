#pragma once

#include <memory>
#include <stack>

namespace Light {
    template<typename T>
    class Node {
    public:
        T data;
        uint32_t priority;
        std::shared_ptr<Node<T>> left;
        std::shared_ptr<Node<T>> right;

        Node(const T& value, uint32_t priority)
            : data(value), priority(priority), left(nullptr), right(nullptr) {
        }
    };

    template<typename T>
    class BinarySearchTree
    {
    public:
        BinarySearchTree() : m_root(nullptr) {}

        ~BinarySearchTree() {}

        void insert(const T& x, uint32_t priority) {
            m_root = insert(x, priority, std::move(m_root));
        }

        void remove(const T& x) {
            m_root = remove(x, std::move(m_root));
        }

        uint32_t& getPriority(const T& x) { return search(x)->priority; }

        std::shared_ptr<Node<T>> search(const T& x) {
            return find(m_root, x);
        }
        class Iterator;

        Iterator begin() {
            return Iterator(m_root);
        }

        Iterator end() {
            return Iterator(nullptr);
        }

    private:
        std::shared_ptr<Node<T>> m_root;

        std::shared_ptr<Node<T>> find(std::shared_ptr<Node<T>> t, const T& x) {
            if (t == nullptr) return nullptr;
            if (x < t->data)
                return find(t->left, x);
            if (x > t->data)
                return find(t->right, x);
            return t;
        }

        std::shared_ptr<Node<T>> insert(const T& x, uint32_t priority, std::shared_ptr<Node<T>> t) {
            if (t == nullptr) {
                return std::make_shared<Node<T>>(x, priority);
            }
            else if (priority < t->priority) {
                t->left = insert(x, priority, std::move(t->left));
            }
            else if (priority > t->priority) {
                t->right = insert(x, priority, std::move(t->right));
            }
            return std::move(t);
        }

        std::shared_ptr<Node<T>> remove(const T& x, std::shared_ptr<Node<T>> t) {
            if (t == nullptr) return nullptr;
            if (x < t->data) {
                t->left = remove(x, std::move(t->left));
            }
            else if (x > t->data) {
                t->right = remove(x, std::move(t->right));
            }
            else if (t->left && t->right) {
                t->data = findMin(t->right)->data;
                t->right = remove(t->data, std::move(t->right));
            }
            else {
                if (t->left == nullptr) {
                    return std::move(t->right);
                }
                else {
                    return std::move(t->left);
                }
            }
            return std::move(t);
        }

        std::shared_ptr<Node<T>> findMin(std::shared_ptr<Node<T>> t) {
            if (t == nullptr) return nullptr;
            while (t->left != nullptr) {
                t = t->left;
            }
            return t;
        }

        // Iterator Class
        class Iterator {
        private:
            std::stack<std::shared_ptr<Node<T>>> stack;

            void pushLeft(std::shared_ptr<Node<T>> node) {
                while (node != nullptr) {
                    stack.push(node);
                    node = node->left;
                }
            }

        public:
            Iterator(std::shared_ptr<Node<T>> root) {
                pushLeft(root);
            }

            T& operator*() {
                return stack.top()->data;
            }

            T* operator->() {
                return &(stack.top()->data);
            }

            Iterator& operator++() {
                std::shared_ptr<Node<T>> node = stack.top();
                stack.pop();
                if (node->right != nullptr) {
                    pushLeft(node->right);
                }
                return *this;
            }

            bool operator!=(const Iterator& other) const {
                return !stack.empty();
            }
        };
    };
}
