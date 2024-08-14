#pragma once

#include "ECS/Entity.h"
#include <unordered_map>
#include <assert.h>

// The one instance of virtual inheritance in the entire implementation.
// An interface is needed so that the ComponentManager
// can tell a generic ComponentArray that an entity has been destroyed
// and that it needs to update its array mappings.

namespace ecs
{
	class IComponentArray
	{
	public:
		virtual ~IComponentArray ( ) = default;
		virtual void EntityDestroyed ( Entity entity ) = 0;
	};


	template<typename T>
	class ComponentArray : public IComponentArray
	{
	public:
		void InsertData ( Entity entity , T component )
		{
			assert ( myEntityToIndexMap.find ( entity ) == myEntityToIndexMap.end ( ) && "Component added to same entity more than once." );

			// Put new entry at end and update the maps
			size_t newIndex = mySize;
			myEntityToIndexMap [ entity ] = newIndex;
			myIndexToEntityMap [ newIndex ] = entity;
			myComponentArray [ newIndex ] = component;
			++mySize;
		}

		void RemoveData ( Entity entity )
		{
			assert ( myEntityToIndexMap.find ( entity ) != myEntityToIndexMap.end ( ) && "Removing non-existent component." );

			// Copy element at end into deleted element's place to maintain density
			size_t indexOfRemovedEntity = myEntityToIndexMap [ entity ];
			size_t indexOfLastElement = mySize - 1;
			myComponentArray [ indexOfRemovedEntity ] = myComponentArray [ indexOfLastElement ];

			// Update map to point to moved spot
			Entity entityOfLastElement = myIndexToEntityMap [ indexOfLastElement ];
			myEntityToIndexMap [ entityOfLastElement ] = indexOfRemovedEntity;
			myIndexToEntityMap [ indexOfRemovedEntity ] = entityOfLastElement;

			myEntityToIndexMap.erase ( entity );
			myIndexToEntityMap.erase ( indexOfLastElement );

			--mySize;
		}

		bool HasData(Entity entity)
		{
			auto component = myEntityToIndexMap.find(entity);
			return (component != myEntityToIndexMap.end());
		}

		T& GetData ( Entity entity )
		{
			assert ( myEntityToIndexMap.find ( entity ) != myEntityToIndexMap.end ( ) && "Retrieving non-existent component." );

			// Return a reference to the entity's component
			return myComponentArray [ myEntityToIndexMap [ entity ] ];
		}

		void EntityDestroyed ( Entity entity ) override
		{
			if ( myEntityToIndexMap.find ( entity ) != myEntityToIndexMap.end ( ) )
			{
				// Remove the entity's component if it existed
				RemoveData ( entity );
			}
		}

	private:
		// The packed array of components (of generic type T),
		// set to a specified maximum amount, matching the maximum number
		// of entities allowed to exist simultaneously, so that each entity
		// has a unique spot.
		std::array<T , MAX_ENTITIES> myComponentArray;

		// Map from an entity ID to an array index.
		std::unordered_map<Entity , size_t> myEntityToIndexMap;

		// Map from an array index to an entity ID.
		std::unordered_map<size_t , Entity> myIndexToEntityMap;

		// Total size of valid entries in the array.
		size_t mySize;
	};
}