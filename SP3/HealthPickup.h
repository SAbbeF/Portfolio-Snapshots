#pragma once
#include "Entity.h"
#include "Observer.h"
#include "GameContext.h"
#include "ParticleEmitter.h"

namespace Game
{
	class Player;
	class HealthPickup : public Entity, public Observer
	{
	public:
		HealthPickup() = default;
		~HealthPickup();

		void Init(GameContext* aGameContext, const std::string aTag, const eUnityTagIDs aTagID);
		bool HandleMessage(eChannels aChannel, const Message& aMessage);

		void Update(GameContext* aGameContext, CollisionManager& aCollisionManager) override;

	private:

		void RotateModel(Tga::Vector3f aAddedRotation);

	private:

		int myHealth;
		float myRotationSpeed;

		ParticleEmitter* myParticleEmitter;
	};
}