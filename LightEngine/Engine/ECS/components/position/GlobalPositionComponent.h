#pragma once
#include <Engine/data/Vec2.h>
#include "../ECS/components/PositionComponent.h"

namespace Light {
	struct GlobalPositionComponent : public PositionComponent
	{
		Vec2 position;

		GlobalPositionComponent(Vec2 pos) : position(pos) {}

		inline Vec2& get() { return position; }
	}; 
}