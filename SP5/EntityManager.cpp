#include "ECS/EntityManager.h"

#include <assert.h>

namespace ecs
{
	EntityManager::EntityManager ( )
	{
		// Initialize the queue with all possible entity IDs
		for ( Entity entity = 0; entity < MAX_ENTITIES; ++entity )
		{
			myAvailableEntities.push ( entity );
		}
	}

	Entity EntityManager::CreateEntity ( )
	{
		assert ( myLivingEntityCount < MAX_ENTITIES && "Too many entities in existence." );

		// Take an ID from the front of the queue
		Entity id = myAvailableEntities.front ( );
		myAvailableEntities.pop ( );
		++myLivingEntityCount;

		return id;
	}

	void EntityManager::DestroyEntity ( Entity entity )
	{
		assert ( entity < MAX_ENTITIES && "Entity out of range." );

		// Invalidate the destroyed entity's signature
		mySignatures [ entity ].reset ( );

		// Put the destroyed ID at the back of the queue
		myAvailableEntities.push ( entity );
		--myLivingEntityCount;
	}

	void EntityManager::SetSignature ( Entity entity , Signature signature )
	{
		assert ( entity < MAX_ENTITIES && "Entity out of range." );

		// Put this entity's signature into the array
		mySignatures [ entity ] = signature;
	}

	Signature EntityManager::GetSignature ( Entity entity )
	{
		assert ( entity < MAX_ENTITIES && "Entity out of range." );

		// Get this entity's signature from the array
		return mySignatures [ entity ];
	}

	void EntityManager::SetUnityID ( Entity entity , int unityId )
	{ 
		assert ( entity < MAX_ENTITIES && "Entity out of range." );
		myUnityID [ entity ] = unityId;
	}

	Entity EntityManager::GetEntityID ( int unity )
	{
		for ( auto const entity : myUnityID )
		{
			if ( entity.second == unity )
			{
				return entity.first;
			}	
		}

		return 0;
	}

	int EntityManager::GetUnityID ( Entity entity )
	{
		return myUnityID [ entity ];
	}
}