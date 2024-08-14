#pragma once

#include "ECS/Entity.h"

#include <queue>
#include <array>
#include <unordered_map>

namespace ecs
{
	class EntityManager
	{
	public:
		EntityManager ( );

		Entity CreateEntity ( );

		void DestroyEntity ( Entity entity );

		void SetSignature ( Entity entity , Signature signature );

		Signature GetSignature ( Entity entity );

		void SetUnityID ( Entity entity , int unityId );

		Entity GetEntityID ( int unity );

		int GetUnityID ( Entity entity );

	private:
		// Queue of unused entity IDs
		std::queue<Entity> myAvailableEntities {};

		// Array of signatures where the index corresponds to the entity ID
		std::array<Signature , MAX_ENTITIES> mySignatures {};

		//Unity ID
		std::unordered_map<Entity , int> myUnityID;

		// Total living entities - used to keep limits on how many exist
		uint32_t myLivingEntityCount {};
	};
}