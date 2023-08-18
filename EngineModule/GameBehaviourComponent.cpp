#include "pch.h"
#include "GameBehaviourComponent.h"

std::list<GameBehaviourComponent*> GameBehaviourComponent::mAllContainerPtr;
std::list<GameBehaviourComponent*> GameBehaviourComponent::mTrueContainerPtr;
std::list<GameBehaviourComponent*> GameBehaviourComponent::mFalseContainerPtr;

GameBehaviourComponent::GameBehaviourComponent()
	: BehaviourComponent(
		reinterpret_cast<std::list<BehaviourComponent*>&>(mAllContainerPtr),
		reinterpret_cast<std::list<BehaviourComponent*>&>(mTrueContainerPtr),
		reinterpret_cast<std::list<BehaviourComponent*>&>(mFalseContainerPtr))
	, mbStarted(false)
{
}

GameBehaviourComponent::~GameBehaviourComponent()
{
}

void GameBehaviourComponent::OnEnable()
{
	for (auto it = mFalseContainerPtr.begin(); it != mFalseContainerPtr.end();)
	{
		if (*it == this)
		{
			mFalseContainerPtr.erase(it);
			break;
		}
	}

	mTrueContainerPtr.emplace_back(this);
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
	for (auto it = mTrueContainerPtr.begin(); it != mTrueContainerPtr.end();)
	{
		if (*it == this)
		{
			mTrueContainerPtr.erase(it);
			break;
		}
	}

	mFalseContainerPtr.emplace_back(this);
}

void GameBehaviourComponent::OnDestroy()
{
}
