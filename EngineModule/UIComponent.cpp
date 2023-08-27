#include "pch.h"
#include "UIComponent.h"

std::vector<UIComponent*> UIComponent::mAllContainerPtr;
std::vector<UIComponent*> UIComponent::mTrueContainerPtr;
std::vector<UIComponent*> UIComponent::mFalseContainerPtr;

UIComponent::UIComponent()
	: BehaviourComponent(reinterpret_cast<std::vector<BehaviourComponent*>&>(mAllContainerPtr))
{
}

UIComponent::~UIComponent()
{
	RemoveThisAllContainer(
		reinterpret_cast<std::vector<BehaviourComponent*>&>(mAllContainerPtr),
		reinterpret_cast<std::vector<BehaviourComponent*>&>(mTrueContainerPtr),
		reinterpret_cast<std::vector<BehaviourComponent*>&>(mFalseContainerPtr));
}

void UIComponent::OnEnable()
{
	InAndOutContainer(reinterpret_cast<std::vector<BehaviourComponent*>&>(mTrueContainerPtr),
		reinterpret_cast<std::vector<BehaviourComponent*>&>(mFalseContainerPtr));
}

void UIComponent::OnDisable()
{
	InAndOutContainer(reinterpret_cast<std::vector<BehaviourComponent*>&>(mFalseContainerPtr),
		reinterpret_cast<std::vector<BehaviourComponent*>&>(mTrueContainerPtr));
}
