#pragma once
#include "Component.h"
#include <tge/math/Transform.h>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <queue>
#include "source/Tools/UnityEnumerations.h"

class GameObject
{
public:

	using id_t = unsigned int;

	GameObject();
	GameObject(eUnityTagIDs aTag);
	virtual ~GameObject();

	GameObject(GameObject&& aGameObjectToMove) noexcept;
	GameObject& operator=(GameObject&& aGameObjectToMove) noexcept;

	virtual inline void Enable() { myIsEnabled = true; }
	virtual inline void Disable() { myIsEnabled = false; }
	virtual void Init();
	virtual void Update(float& aDeltaTime);
	virtual void Render();

	template <typename _Ty, typename... Args> void AddComponent(Args&&... someArgs);
	template <typename _Ty> void AddComponent(std::unique_ptr<_Ty> aComponentPtr);
	template <typename _Ty> _Ty* GetComponent();
	template <typename _Ty> void RemoveComponent();
	void ClearComponents();

	Tga::Transform& GetTransform() { return myTransform; }

	const id_t& GetId() const { return myId; }
	static const id_t& GetId(const GameObject& aGameObject) { return aGameObject.GetId(); }

	const eUnityTagIDs GetTag() const { return myTag; }
	inline bool GetIsEnabled() const { return myIsEnabled; }

protected:

	id_t myId;
	eUnityTagIDs myTag;
	Tga::Transform myTransform;
	std::unordered_map<std::type_index, std::unique_ptr<Component>> myComponents;

private:

	static id_t currentIndex;
	static std::priority_queue<id_t> unclaimedIDs;
	static const id_t GetUniqueId();
	bool myIsEnabled;
	void ReleaseId();
};

template<typename _Ty, typename ...Args> inline void GameObject::AddComponent(Args && ...someArgs)
{
	std::type_index typeIndex = std::type_index(typeid(_Ty));
	myComponents[typeIndex] = std::make_unique<_Ty>(std::forward<Args>(someArgs)...);
}

template<typename _Ty> inline void GameObject::AddComponent(std::unique_ptr<_Ty> aComponentPtr)
{
	std::type_index typeIndex = std::type_index(typeid(_Ty));
	myComponents[typeIndex] = std::move(aComponentPtr);
}

template<typename _Ty> inline _Ty* GameObject::GetComponent()
{
	std::type_index typeIndex = std::type_index(typeid(_Ty));
	auto itr = myComponents.find(typeIndex);
	
	if (itr != myComponents.end())
	{
		return static_cast<_Ty*>(itr->second.get());
	}

	return nullptr;
}

template<typename _Ty> inline void GameObject::RemoveComponent()
{
	myComponents.erase(std::type_index(typeid(_Ty)));
}

inline void GameObject::ClearComponents()
{
	myComponents.clear();
}
