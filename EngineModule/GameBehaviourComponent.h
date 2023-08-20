#pragma once

#include <MathUtil.h>
#include <Vector3.h>
#include <Quaternion.h>
#include <Matrix4x4.h>

#include "InputManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TimeManager.h"

#include "GameObject.h"
#include "Scene.h"
#include "Types.h"

#include "BehaviourComponent.h"

class GameBehaviourComponent : public BehaviourComponent
{
public:
	friend class GameObject;
	friend class Scene;

public:
	GameBehaviourComponent();
	virtual ~GameBehaviourComponent();

protected:	// Game Logic Event.
	virtual void OnEnable() override; // 오버라이딩시 GameBehaviourComponent::OnEnable() 필요.
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void OnDisable() override; // 오버라이딩시 GameBehaviourComponent::OnDisable() 필요.
	virtual void OnDestroy();
	
private:
	static std::list<GameBehaviourComponent*> mAllContainerPtr;
	static std::list<GameBehaviourComponent*> mTrueContainerPtr;
	static std::list<GameBehaviourComponent*> mFalseContainerPtr;

	bool mbStarted;
};

