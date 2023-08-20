#pragma once

#include "Component.h"

class BehaviourComponent : public Component
{
public:
	friend class GameObject;

public:
	BehaviourComponent(std::list<BehaviourComponent*>& allContainer);
	virtual ~BehaviourComponent() = default;

public:
	bool IsActiveAndEnabled() const;
	bool IsEnabled() const;
	void SetEnabled(const bool bEnabled);

protected:
	void InAndOutContainer(std::list<BehaviourComponent*>& inContaier, std::list<BehaviourComponent*>& outContainer);
	void RemoveThisAllContainer(
		std::list<BehaviourComponent*>& allContainer,
		std::list<BehaviourComponent*>& trueContainer,
		std::list<BehaviourComponent*>& falseContainer);

	virtual void OnEnable() abstract;
	virtual void OnDisable() abstract;

protected:
	bool mbEnabled;
};

