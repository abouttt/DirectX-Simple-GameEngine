#include "pch.h"
#include "GameBehaviourComponent.h"

std::vector<GameBehaviourComponent*> GameBehaviourComponent::mAllContainerPtr;
std::vector<GameBehaviourComponent*> GameBehaviourComponent::mTrueContainerPtr;
std::vector<GameBehaviourComponent*> GameBehaviourComponent::mFalseContainerPtr;

GameBehaviourComponent::GameBehaviourComponent()
	: mbStarted(false)
{
	mAllContainerPtr.emplace_back(this);
	OnEnable();
}

GameBehaviourComponent::~GameBehaviourComponent()
{
	RemoveInOrOutContainer(reinterpret_cast<std::vector<BehaviourComponent*>&>(mTrueContainerPtr),
		reinterpret_cast<std::vector<BehaviourComponent*>&>(mFalseContainerPtr));

	auto it = std::find(mAllContainerPtr.begin(), mAllContainerPtr.end(), this);
	if (it != mAllContainerPtr.end())
	{
		mAllContainerPtr.erase(it);
	}
}

void GameBehaviourComponent::OnEnable()
{
	InAndOutContainer(reinterpret_cast<std::vector<BehaviourComponent*>&>(mTrueContainerPtr),
		reinterpret_cast<std::vector<BehaviourComponent*>&>(mFalseContainerPtr));
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
	InAndOutContainer(reinterpret_cast<std::vector<BehaviourComponent*>&>(mFalseContainerPtr),
		reinterpret_cast<std::vector<BehaviourComponent*>&>(mTrueContainerPtr));
}

void GameBehaviourComponent::OnDestroy()
{
}
