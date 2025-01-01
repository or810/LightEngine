#pragma once

#include "../PositionComponent.h"
#include <Engine/data/Vec2.h>
#include "GlobalPositionComponent.h"

namespace Light {
	struct RelativePositionComponent : public PositionComponent 
	{
		GlobalPositionComponent& relative;
		Vec2 offset;
		Vec2 position;

		RelativePositionComponent(GlobalPositionComponent& relativeC, Vec2 offsetC) 
			: relative(relativeC), offset(offsetC) { }

		inline Vec2& get()
		{
			position = relative.position + offset;
			return position;
		}
	};
}