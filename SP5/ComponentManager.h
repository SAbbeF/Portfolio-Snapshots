#pragma once

#include "ECS/IComponentArray.h"
#include <memory>

namespace ecs
{
	class ComponentManager
	{
	public:
		template<typename T>
		void RegisterComponent ( )
		{
			const char* typeName = typeid( T ).name ( );

			assert ( myComponentTypes.find ( typeName ) == myComponentTypes.end ( ) && "Registering component type more than once." );

			// Add this component type to the component type map
			myComponentTypes.insert ( { typeName, myNextComponentType } );

			// Create a ComponentArray pointer and add it to the component arrays map
			myComponentArrays.insert ( { typeName, std::make_shared<ComponentArray<T>> ( ) } );

			// Increment the value so that the next component registered will be different
			++myNextComponentType;
		}

		template<typename T>
		ComponentType GetComponentType ( )
		{
			const char* typeName = typeid( T ).name ( );

			assert ( myComponentTypes.find ( typeName ) != myComponentTypes.end ( ) && "Component not registered before use." );

			// Return this component's type - used for creating signatures
			return myComponentTypes [ typeName ];
		}

		template<typename T>
		void AddComponent ( Entity entity , T component )
		{
			// Add a component to the array for an entity
			GetComponentArray<T> ( )->InsertData ( entity , component );
		}

		template<typename T>
		void RemoveComponent ( Entity entity )
		{
			// Remove a component from the array for an entity
			GetComponentArray<T> ( )->RemoveData ( entity );
		}

		template<typename T>
		bool HasComponent(Entity entity)
		{
			// Check if component exist from the array
			return GetComponentArray<T>()->HasData(entity);
		}

		template<typename T>
		T& GetComponent ( Entity entity )
		{
			// Get a reference to a component from the array for an entity
			return GetComponentArray<T> ( )->GetData ( entity );
		}

		void EntityDestroyed ( Entity entity )
		{
			// Notify each component array that an entity has been destroyed
			// If it has a component for that entity, it will remove it
			for ( auto const& pair : myComponentArrays )
			{
				auto const& component = pair.second;

				component->EntityDestroyed ( entity );
			}
		}

	private:
		// Map from type string pointer to a component type
		std::unordered_map<const char* , ComponentType> myComponentTypes {};

		// Map from type string pointer to a component array
		std::unordered_map<const char* , std::shared_ptr<IComponentArray>> myComponentArrays {};

		// The component type to be assigned to the next registered component - starting at 0
		ComponentType myNextComponentType {};

		// Convenience function to get the statically casted pointer to the ComponentArray of type T.
		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray ( )
		{
			const char* typeName = typeid( T ).name ( );

			assert ( myComponentTypes.find ( typeName ) != myComponentTypes.end ( ) && "Component not registered before use." );

			return std::static_pointer_cast< ComponentArray<T> >( myComponentArrays [ typeName ] );
		}
	};
}