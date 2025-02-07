#pragma once

#include <vector>
#include <functional>
#include <unordered_map>

#include "Engine/EntityComponentSystem/Signature.h"
#include <Engine/EntityComponentSystem/Entities/EntityManager.h>

namespace Light {
	namespace ECS {

		using SystemID = uint32_t;

		class ISystem {
		public:
			virtual ~ISystem() = default;
			virtual void update(const std::vector<Entity>& entities, float deltaTime) = 0;
			Signature getSignature() const { return signature; }

		private:
			Signature signature;
		};
	}
}
