#pragma once

#include "EntityManager.h"

namespace Light {
	

	class IComponentPool {
	protected:
		virtual ~IComponentPool() = default;
		virtual void entityDestroyed(Entity entity) = 0;
	};
}
