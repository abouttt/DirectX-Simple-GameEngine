#pragma once

#include "Component.h"

class BehaviourComponent : public Component
{
public:
	BehaviourComponent(
		std::list<BehaviourComponent*>& allContainerPtrRef,
		std::list<BehaviourComponent*>& trueContainerPtrRef,
		std::list<BehaviourComponent*>& falseContainerPtrRef);
	virtual ~BehaviourComponent();

public:
	bool IsActiveAndEnabled() const;
	bool IsEnabled() const;
	virtual void SetEnabled(const bool bEnabled);

protected:
	void inAndOutContainer(std::list<BehaviourComponent*>& inContaier, std::list<BehaviourComponent*>& outContainer);
	virtual void OnEnable() abstract;
	virtual void OnDisable() abstract;

protected:
	bool mbEnabled;
	std::list<BehaviourComponent*>& mAllContainerPtrRef;
	std::list<BehaviourComponent*>& mTrueContainerPtrRef;
	std::list<BehaviourComponent*>& mFalseContainerPtrRef;
};

