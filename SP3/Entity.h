#pragma once
#include <tge/math/Vector.h>
#include <tge/texture/texture.h>
#include <tge/render/RenderCommon.h>
#include <tge/model/ModelInstance.h>
#include "Model2DAnimator.h"
#include "GameContext.h"
#include "UnityEnumerations.h"

namespace Game
{
	class CollisionManager;
	class BoxCollider;
	class CircleCollider;
	class GameContext;

	struct CollidedInfo
	{
		size_t ID;
		std::string name;
		eUnityTagIDs tag;
		BoxCollider* boxCollider;
		CircleCollider* circleCollider;
	};

	class Entity
	{
	public:

		Entity();
		~Entity();

		virtual void Init(GameContext* aGameContext, const std::string aTag, const eUnityTagIDs aTagID);
		virtual void Update(GameContext* aGameContext, CollisionManager& aCollisionManager);

		void AddBoxCollider(CollisionManager& aCollisionManager);
		void AddBoxCollider(CollisionManager& aCollisionManager, const float someBounds);
		void AddBoxCollider(CollisionManager& aCollisionManager, const Tga::Vector2f someBounds);

		void AddCircleCollider(CollisionManager& aCollisionManager);
		void AddCircleCollider(CollisionManager& aCollisionManager, const float aRaidus);
		void AddCircleCollider(CollisionManager& aCollisionManager, const Tga::Vector2f someBounds);

		void RemoveAllColliders();
		void RemoveAllCollidedEntities();

		const Tga::Vector2f GetPosition();
		virtual void SetPosition(Tga::Vector2f aPosition);
		void AddPosition(Tga::Vector2f aPosition);

		const bool GetIsActive();
		void SetIsActive(bool aFlag);

		const bool GetHasBeenReset();
		void SetHasBeenReset(const bool aFlag);

		const bool GetBoxColliderState();
		void SetBoxColliderState(const bool aFlag);

		const size_t GetID();
		const std::string GetTag();
		const eUnityTagIDs GetTagID();

		BoxCollider* GetBoxCollider();
		CircleCollider* GetCircleCollider();

		const std::vector<CollidedInfo> GetCollidedEnities();
		void SetCollidedEntity(const size_t aID, const std::string aName,
							   eUnityTagIDs aTag, BoxCollider& aBoxCollider, CircleCollider& aCircleCollider);

		void AddModel(std::shared_ptr<Tga::ModelInstance>);
		std::shared_ptr<Tga::ModelInstance> GetModel();

	protected:

		size_t myID;
		std::string myTag;
		eUnityTagIDs myTagID;

		Tga::Vector2f myPosition;
		Tga::Vector2f mySpawnPosition;

		GameContext* myGameContext;
		BoxCollider* myBoxCollider;
		CircleCollider* myCircleCollider;

		std::vector<CollidedInfo> myCollidedEntities;

		std::shared_ptr<Tga::ModelInstance> myModelInstance;

	private:

		size_t GetNextID();

		bool myEntityIsActive;
		bool myEntiyHasBeenReset;
	};
}