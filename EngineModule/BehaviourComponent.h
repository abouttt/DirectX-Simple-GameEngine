#pragma once

#include "Component.h"

class BehaviourComponent : public Component
{
public:
	BehaviourComponent(
		std::list<BehaviourComponent*>* containerPtr,
		std::list<BehaviourComponent*>* enabledTruePtr,
		std::list<BehaviourComponent*>* enabledFalsePtr);
	virtual ~BehaviourComponent();

public:
	bool IsActiveAndEnabled() const;
	bool IsEnabled() const;
	virtual void SetEnabled(const bool bEnabled);

protected:
	void EnabledProcess(bool bEnabled);
	virtual void OnEnable() abstract;
	virtual void OnDisable() abstract;

protected:
	bool mbEnabled;
	std::list<BehaviourComponent*>* mBaseContainerPtr;
	std::list<BehaviourComponent*>* mBaseEnabledTruePtr;
	std::list<BehaviourComponent*>* mBaseEnabledFalsePtr;
};

