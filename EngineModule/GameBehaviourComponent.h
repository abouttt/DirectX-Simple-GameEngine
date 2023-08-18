#pragma once

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
	virtual void OnEnable() override;
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void OnDisable() override;
	virtual void OnDestroy();

private:
	static std::list<GameBehaviourComponent*> mContainerPtr;
	static std::list<GameBehaviourComponent*> mEnabledTruePtr;
	static std::list<GameBehaviourComponent*> mEnabledFalsePtr;
};

