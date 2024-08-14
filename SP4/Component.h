#pragma once
class GameObject;

inline namespace ComponentSystem
{
	class Component
	{
	public:

		Component() = default;
		virtual ~Component() = default;

		Component(const Component& aComponent) = delete;
		Component(Component&& aComponentToMove) noexcept = default;
		Component& operator=(const Component& aComponent) = delete;
		Component& operator=(Component&& aComponentToMove) noexcept = default;

		virtual void Init(GameObject* aParent) = 0;
		virtual void Update(const float& aDeltaTime) { aDeltaTime; }
		virtual void Render() {}

		GameObject* GetParent() const { return myParent; }

	protected:

		GameObject* myParent;
	};
}