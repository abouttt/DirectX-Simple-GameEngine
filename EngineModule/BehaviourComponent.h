#pragma once

#include "Component.h"

class BehaviourComponent : public Component
{
public:
	friend class GameObject;

public:
	BehaviourComponent();
	BehaviourComponent(std::vector<BehaviourComponent*>& allContainer);
	virtual ~BehaviourComponent() = default;

public:
	bool IsActiveAndEnabled() const;
	bool IsEnabled() const;
	void SetEnabled(const bool bEnabled);

protected:
	void InAndOutContainer(std::vector<BehaviourComponent*>& inContaier, std::vector<BehaviourComponent*>& outContainer);
	void RemoveThisAllContainer(
		std::vector<BehaviourComponent*>& allContainer,
		std::vector<BehaviourComponent*>& trueContainer,
		std::vector<BehaviourComponent*>& falseContainer);

	virtual void OnEnable() abstract;
	virtual void OnDisable() abstract;

protected:
	bool mbEnabled;
};

