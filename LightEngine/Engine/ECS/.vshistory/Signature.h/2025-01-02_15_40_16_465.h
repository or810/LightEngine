#pragma once

#include <bitset>
#include <unordered_map>
#include <typeindex>
#include <cassert>
#include "ComponentManager.h"


namespace Light {

    class Signature {

        template<typename Component>
        static void registerComponent() {
            m_typeToIndex.insert[counter++];
        }

        template<typename... Components>
        Signature() 
            : m_signature()
        {
            (m_signature.set(m_typeToIndex[typeid(Components)]), ...)
        }
    private:
        static uint32_t counter;
        static std::unordered_map<std::type_index, uint32_t> m_typeToIndex;
        std::bitset<MAX_COMPONENTS> m_signature;
    };

    uint32_t Signature::counter = 0; 
}


/*
namespace Light {

//#define MAX_COMPONENTS 64  // Max number of components you can have
    class Signature {
    public:

        Signature() = default;

        // Add a component to the signature by its type index
        void addComponent(std::type_index type) {
            size_t index = getComponentIndex(type);
            m_signature.set(index);  // Set the bit for this component type
        }    REMOVE SIGNATURE CLASS

        // Add multiple components to the signature at once using fold expressions
        template<class... T>
        void addComponents() {
            (addComponent(typeid(T)), ...);  // Expand and call addComponent for each type
        }

        // Compare two signatures for equality
        bool operator==(const Signature& other) const {
            return m_signature == other.m_signature;
        }

        bool operator!=(const Signature& other) const {
            return !(*this == other);
        }

        // Static method to register component types with their unique indices
        template<class T>
        static void registerComponentType(size_t index) {
            m_typeToIndexMap[typeid(T)] = index;
        }

        // Check if the signature has a specific component
        bool hasComponent(std::type_index type) const {
            size_t index = getComponentIndex(type);
            return m_signature.test(index);  // Returns true if the bit is set
        }

        // Debug function to print out the signature (for testing purposes)
        void print() const {
            for (size_t i = 0; i < MAX_COMPONENTS; ++i) {
                if (m_signature.test(i)) {
                    std::cout << "Component " << i << " is present." << std::endl;
                }
            }
        }

    private:
        // Get the index of a component type from the static map
        size_t getComponentIndex(std::type_index type) {
            auto it = m_typeToIndexMap.find(type);
            if (it != m_typeToIndexMap.end()) {
                return it->second;
            }

            // If the type is not registered yet, register it and assign an index
            size_t newIndex = m_typeToIndexMap.size();
            m_typeToIndexMap[type] = newIndex;
            return newIndex;
        }

        std::bitset<MAX_COMPONENTS> m_signature;  // Bitset representing the presence of components

        // Static map that associates component types with their bitset index
        static std::unordered_map<std::type_index, size_t> m_typeToIndexMap;
    };

    // Static map initialization
    //std::unordered_map<std::type_index, size_t> Signature::m_typeToIndexMap;

}
*/