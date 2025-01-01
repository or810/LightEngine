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
		void registerSystem(ISystem& system);
		void unregisterSystem(ISystem& system);
		uint32_t tryGetPriority(ISystem& system);
		bool setPriority(ISystem& system, uint32_t newPriority);
		void updateAll(EntitiesArray entities, DeltaTime dt);
	private:
		PriorityQueue<ISystem> m_systems;
	};
}