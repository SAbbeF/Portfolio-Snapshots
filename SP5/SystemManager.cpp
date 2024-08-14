#pragma once
#include "ECS/SystemManager.h"

namespace ecs
{
	void SystemManager::EntityDestroyed ( Entity entity )
	{
		// Erase a destroyed entity from all system lists
		// myEntities is a set so no check needed
		for ( auto const& pair : mySystems )
		{
			auto const& system = pair.second;

			system->myEntities.erase ( entity );
		}
	}

	void SystemManager::EntitySignatureChanged ( Entity entity , Signature entitySignature )
	{
		// Notify each system that an entity's signature changed
		for ( auto const& pair : mySystems )
		{
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = mySignatures [ type ];

			// Entity signature matches system signature - insert into set
			if ( ( entitySignature & systemSignature ) == systemSignature )
			{
				system->myEntities.insert ( entity );
			}
			// Entity signature does not match system signature - erase from set
			else
			{
				system->myEntities.erase ( entity );
			}
		}
	}
}