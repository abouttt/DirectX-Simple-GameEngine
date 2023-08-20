#include "pch.h"
#include "GameBehaviourComponent.h"

std::list<GameBehaviourComponent*> GameBehaviourComponent::mAllContainerPtr;
std::list<GameBehaviourComponent*> GameBehaviourComponent::mTrueContainerPtr;
std::list<GameBehaviourComponent*> GameBehaviourComponent::mFalseContainerPtr;

GameBehaviourComponent::GameBehaviourComponent()
	: BehaviourComponent(reinterpret_cast<std::list<BehaviourComponent*>&>(mAllContainerPtr))
	, mbStarted(false)
{
	OnEnable();
}

GameBehaviourComponent::~GameBehaviourComponent()
{
	RemoveThisAllContainer(
		reinterpret_cast<std::list<BehaviourComponent*>&>(mAllContainerPtr),
		reinterpret_cast<std::list<BehaviourComponent*>&>(mTrueContainerPtr),
		reinterpret_cast<std::list<BehaviourComponent*>&>(mFalseContainerPtr));
}

void GameBehaviourComponent::OnEnable()
{
	InAndOutContainer(reinterpret_cast<std::list<BehaviourComponent*>&>(mTrueContainerPtr),
		reinterpret_cast<std::list<BehaviourComponent*>&>(mFalseContainerPtr));
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
	InAndOutContainer(reinterpret_cast<std::list<BehaviourComponent*>&>(mFalseContainerPtr),
		reinterpret_cast<std::list<BehaviourComponent*>&>(mTrueContainerPtr));
}

void GameBehaviourComponent::OnDestroy()
{
}
