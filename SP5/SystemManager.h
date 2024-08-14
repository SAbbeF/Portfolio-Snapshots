#pragma once

#include "ECS/System.h"

#include <memory>
#include <unordered_map>

namespace ecs
{
	class SystemManager
	{
	public:
		template<typename T>
		std::shared_ptr<T> RegisterSystem ( )
		{
			const char* typeName = typeid( T ).name ( );

			assert ( mySystems.find ( typeName ) == mySystems.end ( ) && "Registering system more than once." );

			// Create a pointer to the system and return it so it can be used externally
			auto system = std::make_shared<T> ( );
			mySystems.insert ( { typeName, system } );
			return system;
		}

		template<typename T>
		void SetSignature ( Signature signature )
		{
			const char* typeName = typeid( T ).name ( );

			assert ( mySystems.find ( typeName ) != mySystems.end ( ) && "System used before registered." );

			// Set the signature for this system
			mySignatures.insert ( { typeName, signature } );
		}

		void EntityDestroyed ( Entity entity );

		void EntitySignatureChanged ( Entity entity , Signature entitySignature );

	private:
		// Map from system type string pointer to a signature
		std::unordered_map<const char* , Signature> mySignatures {};

		// Map from system type string pointer to a system pointer
		std::unordered_map<const char* , std::shared_ptr<System>> mySystems {};
	};
}