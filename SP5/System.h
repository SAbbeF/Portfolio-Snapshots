#pragma once

#include "ECS/Entity.h"
#include <set>

namespace ecs
{
	class System
	{
	public:
		std::set<Entity> myEntities;
	};
}