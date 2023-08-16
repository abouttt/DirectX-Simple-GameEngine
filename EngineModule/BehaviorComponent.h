#pragma once

#include "Component.h"

class BehaviorComponent : public Component
{
public:
	BehaviorComponent();
	virtual ~BehaviorComponent() = default;

public:
	bool IsActiveAndEnabled() const;
	bool IsEnabled() const;
	void SetEnabled(const bool bEnabled);

protected:
	virtual void OnEnable() abstract;
	virtual void OnDisable() abstract;

public:
	bool mbEnabled;
};

