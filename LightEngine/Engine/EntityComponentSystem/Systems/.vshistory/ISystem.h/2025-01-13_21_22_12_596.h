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

		protected:
			std::vector<Entity> activeEntities;
			Signature signature;

			friend class SystemManager;
		};

		class AnonymousSystem : public ISystem {
		public:

			using Func = std::function<void(const std::vector<Entity>&, float)>;

			AnonymousSystem(Signature signature, Func func)
				: updateFunction(std::move(func)) 
			{
				this->signature = std::move(signature);
			}
			
			void update(const std::vector<Entity>& entities, float deltaTime) override
			{
				updateFunction(entities, deltaTime);
			}

		private:
			Func updateFunction;
		};
	}
}
