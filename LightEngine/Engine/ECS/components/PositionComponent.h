#pragma once
#include <Engine/data/Vec2.h>
#include "../ComponentManager.h"

namespace Light {
	struct PositionComponent {

		virtual Vec2& get();
	};
}