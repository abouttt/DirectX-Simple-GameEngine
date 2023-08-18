#include "pch.h"
#include "BehaviourComponent.h"

BehaviourComponent::BehaviourComponent()
    : mbEnabled(true)
{
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

    if (bEnabled)
    {
        OnEnable();
    }
    else
    {
        OnDisable();
    }
}

void BehaviourComponent::InAndOutContainer(std::vector<BehaviourComponent*>& inContaier, std::vector<BehaviourComponent*>& outContainer)
{
    auto it = std::find(outContainer.begin(), outContainer.end(), this);
    if (it != outContainer.end())
    {
        outContainer.erase(it);
    }

    inContaier.emplace_back(this);
}

void BehaviourComponent::RemoveThisInAndOutContainer(std::vector<BehaviourComponent*>& inContaier, std::vector<BehaviourComponent*>& outContainer)
{
    if (IsEnabled())
    {
        auto it = std::find(inContaier.begin(), inContaier.end(), this);
        if (it != inContaier.end())
        {
            inContaier.erase(it);
        }
    }
    else
    {
        auto it = std::find(outContainer.begin(), outContainer.end(), this);
        if (it != outContainer.end())
        {
            outContainer.erase(it);
        }
    }
}
