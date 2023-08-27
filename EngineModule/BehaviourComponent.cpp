#include "pch.h"
#include "BehaviourComponent.h"

BehaviourComponent::BehaviourComponent()
    : mbEnabled(true)
{
}

BehaviourComponent::BehaviourComponent(std::vector<BehaviourComponent*>& allContainer)
    : mbEnabled(true)
{
    allContainer.push_back(this);
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
    if (IsDestroyed())
    {
        return;
    }

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

    inContaier.push_back(this);
}

void BehaviourComponent::RemoveThisAllContainer(
    std::vector<BehaviourComponent*>& allContainer,
    std::vector<BehaviourComponent*>& trueContainer,
    std::vector<BehaviourComponent*>& falseContainer)
{
    if (IsEnabled())
    {
        trueContainer.erase(std::find(trueContainer.begin(), trueContainer.end(), this));
    }
    else
    {
        falseContainer.erase(std::find(falseContainer.begin(), falseContainer.end(), this));
    }

    allContainer.erase(std::find(allContainer.begin(), allContainer.end(), this));
}
