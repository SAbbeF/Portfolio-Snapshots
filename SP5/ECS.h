#pragma once

#include "ECS/EntityManager.h"
#include "ECS/ComponentManager.h"
#include "ECS/SystemManager.h"

namespace ecs
{
	class ECS
	{
	public:
		void Init ( )
		{
			// Create pointers to each manager
			myEntityManager = std::make_unique<EntityManager> ( );
			myComponentManager = std::make_unique<ComponentManager> ( );
			mySystemManager = std::make_unique<SystemManager> ( );
		}

		void Reset()
		{
			myEntityManager.reset();
			myComponentManager.reset();
			mySystemManager.reset();
		}

		// Entity methods
		Entity CreateEntity ( )
		{
			return myEntityManager->CreateEntity ( );
		}

		Entity GetEntityID(int unityID)
		{
			return myEntityManager->GetEntityID(unityID);
		}

		void DestroyEntity(Entity entity)
		{
			myEntityManager->DestroyEntity(entity);

			myComponentManager->EntityDestroyed(entity);

			mySystemManager->EntityDestroyed(entity);
		}

		//Unity ID
		void SetUnityID ( Entity entity , int unityID)
		{
			myEntityManager->SetUnityID ( entity , unityID );
		}

		int GetUnityID ( Entity entity )
		{
			return myEntityManager->GetUnityID ( entity );
		}

		// Component methods
		template<typename T>
		void RegisterComponent ( )
		{
			myComponentManager->RegisterComponent<T> ( );
		}

		template<typename T>
		void AddComponent ( Entity entity , T component )
		{
			myComponentManager->AddComponent<T> ( entity , component );

			auto signature = myEntityManager->GetSignature ( entity );
			signature.set ( myComponentManager->GetComponentType<T> ( ) , true );
			myEntityManager->SetSignature ( entity , signature );

			mySystemManager->EntitySignatureChanged ( entity , signature );
		}

		template<typename T>
		void RemoveComponent ( Entity entity )
		{
			myComponentManager->RemoveComponent<T> ( entity );

			auto signature = myEntityManager->GetSignature ( entity );
			signature.set ( myComponentManager->GetComponentType<T> ( ) , false );
			myEntityManager->SetSignature ( entity , signature );

			mySystemManager->EntitySignatureChanged ( entity , signature );
		}

		template<typename T>
		bool HasComponent(Entity entity)
		{
			return myComponentManager->HasComponent<T>(entity);
		}

		template<typename T>
		T& GetComponent ( Entity entity )
		{
			return myComponentManager->GetComponent<T> ( entity );
		}

		template<typename T>
		ComponentType GetComponentType ( )
		{
			return myComponentManager->GetComponentType<T> ( );
		}


		// System methods
		template<typename T>
		std::shared_ptr<T> RegisterSystem ( )
		{
			return mySystemManager->RegisterSystem<T> ( );
		}

		template<typename T>
		void SetSystemSignature ( Signature signature )
		{
			mySystemManager->SetSignature<T> ( signature );
		}

	private:

		std::unique_ptr<EntityManager> myEntityManager;
		std::unique_ptr<ComponentManager> myComponentManager;
		std::unique_ptr<SystemManager> mySystemManager;
	};
}

using ecs::ECS;