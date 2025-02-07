#pragma once

#include <bitset>

namespace Light {
	namespace ECS {
		
		constexpr size_t MAX_COMPONENTS = 64;

		using ComponentID = uint32_t;
		using Signature = std::bitset<MAX_COMPONENTS>;

		class Signature {
		public:

			template<typename... Cs>
			static Signature createSignature()
			{
				Signature signature;
				(signature.set(getComponentID<Cs>()), ...);
				return signature;
			}

			template<typename C>
			static ComponentID getComponentID()
			{
				static ComponentID id = counter++;
				return id;
			}

		private:
			static inline ComponentID counter = 0;
		};
	}
}
