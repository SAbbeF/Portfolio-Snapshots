#pragma once
#include "Component.h"
#include <string>
#include <memory>

namespace Tga
{
	class ModelInstance;
}

inline namespace ComponentSystem
{
	class VisualComponent : public Component
	{
	public:

		VisualComponent(const std::string& aFilePath);
		VisualComponent(const Tga::ModelInstance& aModelInstance);

		VisualComponent(VisualComponent&& aVisualComponentToMove) noexcept;
		VisualComponent& operator=(VisualComponent&& aVisualComponentToMove) noexcept;

		void Init(GameObject* aParent) override;
		void Update(const float& aDeltaTime);
		void Render();

		Tga::ModelInstance& GetModelInstance() const;

		void SetModelInstance(const Tga::ModelInstance& aModelInstance);
		void SetModelInstance(const std::string& aFilePath);

	private:

		std::unique_ptr<Tga::ModelInstance> myModelInstance = nullptr;
	};
}