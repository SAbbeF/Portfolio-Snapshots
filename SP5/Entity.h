#pragma once
#include <cstdint>
#include <bitset>

namespace ecs
{
	//A simple type alias
	using Entity = std::uint32_t;

	//Size of arrays for entities
	const Entity MAX_ENTITIES = 5000;

	//A simple type alias
	using ComponentType = std::uint8_t;

	//Size of arrays for comps
	const ComponentType MAX_COMPONENT = 32;

	//A simple type alias
	using Signature = std::bitset<MAX_COMPONENT>;
}

using ecs::Entity;