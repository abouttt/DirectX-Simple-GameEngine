#include "pch.h"
#include "UIComponent.h"

std::list<UIComponent*> UIComponent::mAllContainerPtr;
std::list<UIComponent*> UIComponent::mTrueContainerPtr;
std::list<UIComponent*> UIComponent::mFalseContainerPtr;

UIComponent::UIComponent()
	: BehaviourComponent(reinterpret_cast<std::list<BehaviourComponent*>&>(mAllContainerPtr))
{
	OnEnable();
}

UIComponent::~UIComponent()
{
	RemoveThisAllContainer(
		reinterpret_cast<std::list<BehaviourComponent*>&>(mAllContainerPtr),
		reinterpret_cast<std::list<BehaviourComponent*>&>(mTrueContainerPtr),
		reinterpret_cast<std::list<BehaviourComponent*>&>(mFalseContainerPtr));
}

void UIComponent::OnEnable()
{
	InAndOutContainer(reinterpret_cast<std::list<BehaviourComponent*>&>(mTrueContainerPtr),
		reinterpret_cast<std::list<BehaviourComponent*>&>(mFalseContainerPtr));
}

void UIComponent::OnDisable()
{
	InAndOutContainer(reinterpret_cast<std::list<BehaviourComponent*>&>(mFalseContainerPtr),
		reinterpret_cast<std::list<BehaviourComponent*>&>(mTrueContainerPtr));
}
