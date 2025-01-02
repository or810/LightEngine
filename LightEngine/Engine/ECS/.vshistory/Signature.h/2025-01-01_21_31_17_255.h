#pragma once

#include <type_traits>
#include "ComponentManager.h"
#include <bitset>

namespace Light {
    class Signature
    {
    public:
        template <class... T>
        static Signature& CreateSignature() {
            Signature& signature;
            (signature.m_signature.set(typeid(T)), ...);
            return signature;
        }

        template <class T>
        bool addComponent() {
            m_signature.set(typeid(T));
        }

        inline bool operator==(Signature other) {
            return m_signature == other.m_signature;
        }

    private:
        Signature() = default;
    private:
        std::bitset<MAX_COMPONENTS> m_signature;
    };
}