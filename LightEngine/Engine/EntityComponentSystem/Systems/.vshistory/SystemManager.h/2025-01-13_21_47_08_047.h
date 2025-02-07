#pragma once

#include <memory>

#include "Engine/EntityComponentSystem/Systems/ISystem.h"

namespace Light {
	namespace ECS {

		class SystemManager {
		public:

            template <typename T, typename... Args>
            T* registerSystem(Args&&... args) {
                SystemID id = systemCounter++;
                auto system = std::make_unique<T>(std::forward<Args>(args)...);
                T* systemPtr = static_cast<T*>(system.get());
                systems[id] = std::move(system);
                return systemPtr;
            }

            void updateSystems(float deltaTime) {
                for (auto& [id, system] : systems) {
                    system->update(deltaTime);
                }
            }

            void setSystemSignature(SystemID id, Signature signature) {
                systemSignatures[id] = std::move(signature);
                auto it = systems.find(id);
                if (it != systems.end()) {
                    it->second->signature = systemSignatures[id];
                    UpdateSystemEntities(id);
                }
            }

            void entityDestroyed(Entity entity) {
                for (auto& [id, system] : systems) {
                    auto& entities = system->activeEntities;
                    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
                }
            }

            void entitySignatureChanged(Entity entity, Signature entitySignature) {
                for (auto& [id, system] : systems) {
                    const auto& systemSignature = systemSignatures[id];
                    auto& entities = system->activeEntities;

                    if ((entitySignature & systemSignature) == systemSignature) {
                        if (std::find(entities.begin(), entities.end(), entity) == entities.end()) {
                            entities.push_back(entity);
                        }
                    }
                    else {
                        entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
                    }
                }
            }

		private:
			std::unordered_map<SystemID, std::unique_ptr<ISystem>> systems;
			std::unordered_map<SystemID, Signature> systemSignatures;
			SystemID systemCounter = 0;
			

			std::unordered_map<Entity, Signature> entitySignatures;
		
		private:
			void updateSystemEntities(SystemID id) {
				auto it = systems.find(id);
				if (it == systems.end()) return;

				auto& system = it->second;
				system->activeEntities.clear();
				for (const auto& [entity, entitySignature] : entitySignatures) {
					if ((entitySignature & system->signature) == system->signature) {
						system->activeEntities.push_back(entity);
					}
				}
			}
		};
	}
}
