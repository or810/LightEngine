#pragma once

#include <memory>
#include <vector>
#include "ISystem.h"
#include "Engine/data/Sequence.h"
#include "Engine/data/DeltaTime.h"


namespace Light{

	class SystemManager
	{
	public:

		SystemManager() : m_systems() {}

		void registerSystem(std::shared_ptr<ISystem> system);

		void unregisterSystem(std::shared_ptr<ISystem> system);

		uint32_t tryGetPriority(std::shared_ptr<ISystem> system);

		bool setPriority(std::shared_ptr<ISystem> system, uint32_t newPriority);

		void updateAll(EntitiesArray entities, DeltaTime dt);
	private:
		PriorityQueue<ISystem> m_systems;
	};
}