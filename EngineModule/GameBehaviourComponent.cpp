#include "pch.h"
#include "GameBehaviourComponent.h"

std::list<GameBehaviourComponent*> GameBehaviourComponent::mContainerPtr;
std::list<GameBehaviourComponent*> GameBehaviourComponent::mEnabledTruePtr;
std::list<GameBehaviourComponent*> GameBehaviourComponent::mEnabledFalsePtr;

GameBehaviourComponent::GameBehaviourComponent()
	: BehaviourComponent(
		reinterpret_cast<std::list<BehaviourComponent*>*>(&mContainerPtr),
		reinterpret_cast<std::list<BehaviourComponent*>*>(&mEnabledTruePtr),
		reinterpret_cast<std::list<BehaviourComponent*>*>(&mEnabledFalsePtr))
{
}

GameBehaviourComponent::~GameBehaviourComponent()
{
}

void GameBehaviourComponent::OnEnable()
{
	for (auto it = mEnabledFalsePtr.begin(); it != mEnabledFalsePtr.end();)
	{
		if (*it == this)
		{
			mEnabledFalsePtr.erase(it);
			break;
		}
	}

	mEnabledTruePtr.emplace_back(this);
}

void GameBehaviourComponent::Start()
{
}

void GameBehaviourComponent::Update()
{
}

void GameBehaviourComponent::LateUpdate()
{
}

void GameBehaviourComponent::OnDisable()
{
	for (auto it = mEnabledTruePtr.begin(); it != mEnabledTruePtr.end();)
	{
		if (*it == this)
		{
			mEnabledTruePtr.erase(it);
			break;
		}
	}

	mEnabledFalsePtr.emplace_back(this);
}

void GameBehaviourComponent::OnDestroy()
{
}
