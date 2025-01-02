#pragma once

#include <set>
#include <type_traits>
#include "ComponentManager.h"
#include <bitset>
#include <typeindex>

namespace Light {

    class Signature {
    public:
        // Add a component to the signature using std::type_index
        void addComponent(size_t type) {
            size_t index = getComponentIndex(type);
            m_signature.set(index);
        }

        // Add multiple components at once using fold expressions
        template<class... T>
        void addComponents() {
            (addComponent(typeid(T)), ...);
        }

        // Compare signatures for equality
        inline bool operator==(const Signature& other) const {
            return m_signature == other.m_signature;
        }

        // Register a component type and assign it a unique index
        template <class T>
        static void registerComponentType(size_t index) {
            m_typeToIndexMap[typeid(T)] = index;
        }

    private:
        // Helper to map std::type_index to a bitset position
        size_t getComponentIndex(std::type_index type) {
            auto it = m_typeToIndexMap.find(type);
            if (it != m_typeToIndexMap.end()) {
                return it->second;
            }

            // Generate a new index for new component types
            size_t index = m_typeToIndexMap.size();
            m_typeToIndexMap[type] = index;
            return index;
        }

        std::bitset<MAX_COMPONENTS> m_signature;   // Holds the component presence information
        static std::unordered_map<std::type_index, size_t> m_typeToIndexMap;  // Maps type to a bitset index
    };

    // Static map that associates component types with their indices in the bitset
    std::unordered_map<std::type_index, size_t> Signature::m_typeToIndexMap;

}
