#include "pch.h"
#include "BehaviourComponent.h"

BehaviourComponent::BehaviourComponent(
	std::list<BehaviourComponent*>& allContainerPtrRef,
	std::list<BehaviourComponent*>& trueContainerPtrRef,
	std::list<BehaviourComponent*>& falseContainerPtrRef)
    : mbEnabled(true)
	, mAllContainerPtrRef(allContainerPtrRef)
	, mTrueContainerPtrRef(trueContainerPtrRef)
	, mFalseContainerPtrRef(falseContainerPtrRef)
{
	mAllContainerPtrRef.emplace_back(this);
	inAndOutContainer(mTrueContainerPtrRef, mFalseContainerPtrRef);
}

BehaviourComponent::~BehaviourComponent()
{
	for (auto it = mAllContainerPtrRef.begin(); it != mAllContainerPtrRef.end();)
	{
		if (*it == this)
		{
			mAllContainerPtrRef.erase(it);
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

	if (bEnabled)
	{
		inAndOutContainer(mTrueContainerPtrRef, mFalseContainerPtrRef);
	}
	else
	{
		inAndOutContainer(mFalseContainerPtrRef, mTrueContainerPtrRef);
	}

    if (!IsActive())
    {
        return;
    }

    if (bEnabled)
    {
        OnEnable();
    }
    else
    {
        OnDisable();
    }
}

void BehaviourComponent::inAndOutContainer(std::list<BehaviourComponent*>& inContaier, std::list<BehaviourComponent*>& outContainer)
{
	for (auto it = outContainer.begin(); it != outContainer.end();)
	{
		if (*it == this)
		{
			outContainer.erase(it);
			break;
		}
	}

	inContaier.emplace_back(this);
}
