#pragma once
#include <vector>
#include <tge/drawers/DebugDrawer.h>
#include "tge/math/Vector.h"

namespace Game
{
	class BoxCollider;
	class CircleCollider;
	class Entity;
	enum class eUnityTagIDs;

	class CollisionManager
	{
	private:

		friend BoxCollider;
		friend CircleCollider;

	public:

		CollisionManager();
		~CollisionManager();

		BoxCollider* AddBoxCollider(Entity* anEntity);
		BoxCollider* AddBoxCollider(Entity* anEntity, const float someBounds);
		BoxCollider* AddBoxCollider(Entity* anEntity, Tga::Vector2f aBoundBox);

		CircleCollider* AddCircleCollider(Entity* anEntity);
		CircleCollider* AddCircleCollider(Entity* anEntity, const float aRaidus);
		CircleCollider* AddCircleCollider(Entity* anEntity, Tga::Vector2f aBoundBox);

		void Update();
		void DrawColliders();

	private:

		void UpdateBoxCollisions();
		void UpdateCircleBoxCollisions();
		void UpdateCircleCollisions();

		void RemoveBoxCollider(Game::BoxCollider* aBoxCollider);
		void RemoveCircleCollider(std::shared_ptr<Game::CircleCollider> aCircleCollider);

		bool AreCollidersTagCompatible(eUnityTagIDs aFirstTag, eUnityTagIDs aSecondTag);

		bool IsColliding(const std::shared_ptr<Game::BoxCollider> aColliderA, const std::shared_ptr<Game::BoxCollider> aColliderB) const;
		bool IsColliding(std::shared_ptr<Game::CircleCollider> aCCollider, const  std::shared_ptr<Game::BoxCollider> aBCollider) const;
		bool IsColliding(std::shared_ptr<Game::CircleCollider> aColliderA, std::shared_ptr<Game::CircleCollider> aColliderB) const;

	private:

		std::vector<std::shared_ptr<Game::BoxCollider>> myBoxColliders;
		std::vector<std::shared_ptr<Game::CircleCollider>> myCircleColliders;
	};
}