#include "pch.h"
#include "BehaviourComponent.h"

BehaviourComponent::BehaviourComponent(
	std::list<BehaviourComponent*>* containerPtr,
	std::list<BehaviourComponent*>* enabledTruePtr,
	std::list<BehaviourComponent*>* enabledFalsePtr)
    : mbEnabled(true)
	, mBaseContainerPtr(containerPtr)
	, mBaseEnabledTruePtr(enabledTruePtr)
	, mBaseEnabledFalsePtr(enabledFalsePtr)
{
	mBaseContainerPtr->emplace_back(this);
	EnabledProcess(true);
}

BehaviourComponent::~BehaviourComponent()
{
	for (auto it = mBaseContainerPtr->begin(); it != mBaseContainerPtr->end();)
	{
		if (*it == this)
		{
			mBaseContainerPtr->erase(it);
			break;
		}
	}
}

bool BehaviourComponent::IsActiveAndEnabled() const
{
    return IsActive() && mbEnabled;
}

bool BehaviourComponent::IsEnabled() const
{
    return mbEnabled;
}

void BehaviourComponent::SetEnabled(const bool bEnabled)
{
    if (mbEnabled == bEnabled)
    {
        return;
    }

    mbEnabled = bEnabled;

    if (!IsActive())
    {
        return;
    }

	EnabledProcess(bEnabled);

    if (bEnabled)
    {
        OnEnable();
    }
    else
    {
        OnDisable();
    }
}

void BehaviourComponent::EnabledProcess(bool bEnabled)
{
	if (bEnabled)
	{
		for (auto it = mBaseEnabledFalsePtr->begin(); it != mBaseEnabledFalsePtr->end();)
		{
			if (*it == this)
			{
				mBaseEnabledFalsePtr->erase(it);
				break;
			}
		}

		mBaseEnabledTruePtr->emplace_back(this);
	}
	else
	{
		for (auto it = mBaseEnabledTruePtr->begin(); it != mBaseEnabledTruePtr->end();)
		{
			if (*it == this)
			{
				mBaseEnabledTruePtr->erase(it);
				break;
			}
		}

		mBaseEnabledFalsePtr->emplace_back(this);
	}
}
