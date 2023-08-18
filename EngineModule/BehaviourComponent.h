#pragma once

#include "Component.h"

class BehaviourComponent : public Component
{
public:
	friend class GameObject;

public:
	BehaviourComponent();
	virtual ~BehaviourComponent() = default;

public:
	bool IsActiveAndEnabled() const;
	bool IsEnabled() const;
	virtual void SetEnabled(const bool bEnabled);

protected:
	void InAndOutContainer(std::vector<BehaviourComponent*>& inContaier, std::vector<BehaviourComponent*>& outContainer);
	virtual void OnEnable() abstract;
	virtual void OnDisable() abstract;

protected:
	bool mbEnabled;
};

