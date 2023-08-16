#include "pch.h"
#include "BehaviorComponent.h"

BehaviorComponent::BehaviorComponent()
    : mbEnabled(false)
{
}

bool BehaviorComponent::IsActiveAndEnabled() const
{
    return IsActive() && mbEnabled;
}

bool BehaviorComponent::IsEnabled() const
{
    return mbEnabled;
}

void BehaviorComponent::SetEnabled(const bool bEnabled)
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

    if (bEnabled)
    {
        OnEnable();
    }
    else
    {
        OnDisable();
    }
}
