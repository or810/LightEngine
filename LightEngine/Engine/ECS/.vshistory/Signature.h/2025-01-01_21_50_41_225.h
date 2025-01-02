#pragma once

#include "ComponentManager.h"
#include <cassert>
#include <typeindex>
#include <type_traits>
#include <bitset>
#include <bitset>
namespace Light {
    class Signature {
    public:
        Signature() = default;

        template <typename T>
        void addComponent() {
            size_t index = typeToIndex(typeid(T));
            if (index < MAX_COMPONENTS) { // Check if index is within bounds
                m_signature.set(index);
            }
            else {
                //Handle the error, throw exception, log message, etc.
                assert(false && "Component type exceeds MAX_COMPONENTS. Increase MAX_COMPONENTS or register fewer components.");
            }
        }

        bool operator==(const Signature& other) const {
            return m_signature == other.m_signature;
        }

        bool operator!=(const Signature& other) const {
            return !(*this == other);
        }

        std::bitset<MAX_COMPONENTS> getSignature() const { return m_signature; }

    private:
        std::bitset<MAX_COMPONENTS> m_signature;

        // Runtime mapping of type_info to index
        static std::unordered_map<std::type_index, size_t> typeIndexMap;
        static size_t nextIndex;

        static size_t typeToIndex(const std::type_info& type) {
            std::type_index typeIndex(type);
            auto it = typeIndexMap.find(typeIndex);
            if (it != typeIndexMap.end()) {
                return it->second;
            }
            else {
                if (nextIndex < MAX_COMPONENTS)
                {
                    typeIndexMap[typeIndex] = nextIndex;
                    return nextIndex++;
                }
                else
                {
                    assert(false && "Component type exceeds MAX_COMPONENTS. Increase MAX_COMPONENTS or register fewer components.");
                    return MAX_COMPONENTS; //Return an invalid index
                }
            }
        }
    };

    std::unordered_map<std::type_index, size_t> Signature::typeIndexMap;
    size_t Signature::nextIndex = 0;
}