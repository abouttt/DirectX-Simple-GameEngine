#include "pch.h"
#include "GameBehaviourComponent.h"

std::vector<GameBehaviourComponent*> GameBehaviourComponent::mAllContainerPtr;
std::vector<GameBehaviourComponent*> GameBehaviourComponent::mTrueContainerPtr;
std::vector<GameBehaviourComponent*> GameBehaviourComponent::mFalseContainerPtr;

GameBehaviourComponent::GameBehaviourComponent()
	: BehaviourComponent(reinterpret_cast<std::vector<BehaviourComponent*>&>(mAllContainerPtr))
	, mbStarted(false)
{
}

GameBehaviourComponent::~GameBehaviourComponent()
{
	RemoveThisAllContainer(
		reinterpret_cast<std::vector<BehaviourComponent*>&>(mAllContainerPtr),
		reinterpret_cast<std::vector<BehaviourComponent*>&>(mTrueContainerPtr),
		reinterpret_cast<std::vector<BehaviourComponent*>&>(mFalseContainerPtr));
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
