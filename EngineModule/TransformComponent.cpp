#include "pch.h"

#include <Matrix4x4.h>
#include <Quaternion.h>

#include "TransformComponent.h"

TransformComponent::TransformComponent()
	: mLocalTransform()
	, mWorldTransform()
	, mParentPtr(nullptr)
	, mChildrenPtr()
{
}

TransformComponent::TransformComponent(const Transform& localTransform)
	: mLocalTransform(localTransform)
	, mWorldTransform()
	, mParentPtr(nullptr)
	, mChildrenPtr()
{
	updateWorld();
}

Vector3 TransformComponent::GetLocalPosition() const
{
	return mLocalTransform.GetPosition();
}

Quaternion TransformComponent::GetLocalRotation() const
{
	return mLocalTransform.GetRotation();
}

Vector3 TransformComponent::GetLocalEulerAngles() const
{
	return mLocalTransform.GetEulerAngles();
}

Vector3 TransformComponent::GetLocalScale() const
{
	return mLocalTransform.GetScale();
}

Vector3 TransformComponent::GetLocalAxisX() const
{
	return mLocalTransform.GetAxisX();
}

Vector3 TransformComponent::GetLocalAxisY() const
{
	return mLocalTransform.GetAxisY();
}

Vector3 TransformComponent::GetLocalAxisZ() const
{
	return mLocalTransform.GetAxisZ();
}

Matrix4x4 TransformComponent::GetLocalMatrix() const
{
	return mLocalTransform.GetMatrix();
}

void TransformComponent::SetLocalPosition(const Vector3& position)
{
	mLocalTransform.SetPosition(position);
	updateWorld();
}

void TransformComponent::SetLocalRotation(const Quaternion& rotation)
{
	mLocalTransform.SetRotation(rotation);
	updateWorld();
}

void TransformComponent::SetLocalRotation(const Vector3& eulerAngles)
{
	mLocalTransform.SetRotation(eulerAngles);
	updateWorld();
}

void TransformComponent::SetLocalScale(const Vector3& scale)
{
	mLocalTransform.SetScale(scale);
	updateWorld();
}

void TransformComponent::AddLocalPosition(const Vector3& position)
{
	mLocalTransform.AddPosition(position);
	updateWorld();
}

void TransformComponent::AddLocalRotation(const Vector3& eulerAngles)
{
	mLocalTransform.AddRotation(eulerAngles);
	updateWorld();
}

void TransformComponent::AddLocalScale(const Vector3& scale)
{
	mLocalTransform.AddScale(scale);
	updateWorld();
}

void TransformComponent::AddLocalRotationX(const float degree)
{
	mLocalTransform.AddRotationX(degree);
	updateWorld();
}

void TransformComponent::AddLocalRotationY(const float degree)
{
	mLocalTransform.AddRotationY(degree);
	updateWorld();
}

void TransformComponent::AddLocalRotationZ(const float degree)
{
	mLocalTransform.AddRotationZ(degree);
	updateWorld();
}

void TransformComponent::Translate(const Vector3& translation)
{
	mLocalTransform.Translate(translation);
	updateWorld();
}

void TransformComponent::LookAt(const TransformComponent* const target)
{
	mWorldTransform.LookAt(target->mWorldTransform);
	updateLocal();
}

Vector3 TransformComponent::GetPosition() const
{
	return mWorldTransform.GetPosition();
}

Quaternion TransformComponent::GetRotation() const
{
	return mWorldTransform.GetRotation();
}

Vector3 TransformComponent::GetEulerAngles() const
{
	return mWorldTransform.GetEulerAngles();
}

Vector3 TransformComponent::GetScale() const
{
	return mWorldTransform.GetScale();
}

Vector3 TransformComponent::GetAxisX() const
{
	return mWorldTransform.GetAxisX();
}

Vector3 TransformComponent::GetAxisY() const
{
	return mWorldTransform.GetAxisY();
}

Vector3 TransformComponent::GetAxisZ() const
{
	return mWorldTransform.GetAxisZ();
}

Matrix4x4 TransformComponent::GetMatrix() const
{
	return mWorldTransform.GetMatrix();
}

void TransformComponent::SetPosition(const Vector3& position)
{
	mWorldTransform.SetPosition(position);
	updateLocal();
}

void TransformComponent::SetRotation(const Quaternion& rotation)
{
	mWorldTransform.SetRotation(rotation);
	updateLocal();
}

void TransformComponent::SetRotation(const Vector3& eulerAngles)
{
	mWorldTransform.SetRotation(eulerAngles);
	updateLocal();
}

void TransformComponent::SetScale(const Vector3& scale)
{
	mWorldTransform.SetScale(scale);
	updateLocal();
}

void TransformComponent::AddPosition(const Vector3& position)
{
	mWorldTransform.AddPosition(position);
	updateLocal();
}

void TransformComponent::AddRotation(const Vector3& eulerAngles)
{
	mWorldTransform.AddRotation(eulerAngles);
	updateLocal();
}

void TransformComponent::AddScale(const Vector3& scale)
{
	mWorldTransform.AddScale(scale);
	updateLocal();
}

void TransformComponent::AddRotationX(const float degree)
{
	mWorldTransform.AddRotationX(degree);
	updateLocal();
}

void TransformComponent::AddRotationY(const float degree)
{
	mWorldTransform.AddRotationY(degree);
	updateLocal();
}

void TransformComponent::AddRotationZ(const float degree)
{
	mWorldTransform.AddRotationZ(degree);
	updateLocal();
}

TransformComponent* TransformComponent::FindChild(const std::wstring& name)
{
	for (auto child : mChildrenPtr)
	{
		if (child->GetName() == name)
		{
			return child;
		}
	}

	return nullptr;
}

TransformComponent* TransformComponent::GetChild(const std::size_t index)
{
	if (index >= 0 && index < mChildrenPtr.size())
	{
		return mChildrenPtr[index];
	}

	return nullptr;
}

bool TransformComponent::IsChildOf(const TransformComponent* const child)
{
	return std::find(mChildrenPtr.begin(), mChildrenPtr.end(), child) != mChildrenPtr.end() ? true : false;
}

std::size_t TransformComponent::GetChildCount()
{
	return mChildrenPtr.size();
}

void TransformComponent::DetachChildren()
{
	for (auto child : mChildrenPtr)
	{
		child->SetParent(nullptr);
	}
}

TransformComponent* TransformComponent::GetRoot()
{
	TransformComponent* parent = nullptr;
	TransformComponent* current = this;
	while ((parent = current->GetParent()) != nullptr)
	{
		current = parent;
	}

	return current;
}

bool TransformComponent::HasParent()
{
	return mParentPtr != nullptr;
}

TransformComponent* TransformComponent::GetParent()
{
	return mParentPtr;
}

void TransformComponent::SetParent(TransformComponent* const parent)
{
	if (parent)
	{
		if (mParentPtr == parent)
		{
			return;
		}

		// 새로운 트랜스폼 노드로 부모 재설정.
		removeFromParent();
		parent->mChildrenPtr.push_back(this);
		mParentPtr = parent;

		// 새로운 부모에 맞춰 자신의 로컬 정보를 업데이트한다.
		updateLocal();
	}
	else
	{
		removeFromParent();
	}
}

void TransformComponent::removeFromParent()
{
	if (!HasParent())
	{
		return;
	}

	auto& parentChildren = mParentPtr->mChildrenPtr;
	mParentPtr->mChildrenPtr.erase(std::find(parentChildren.begin(), parentChildren.end(), this));
	mParentPtr = nullptr;
	updateLocal();
}

void TransformComponent::updateLocal()
{
	if (HasParent())
	{
		mLocalTransform = mWorldTransform.GetWorldToLocal(mParentPtr->mWorldTransform);
	}
	else
	{
		mLocalTransform = mWorldTransform;
	}

	updateChildrenWorld();
}

void TransformComponent::updateWorld()
{
	if (HasParent())
	{
		mWorldTransform = mLocalTransform.GetLocalToWorld(mParentPtr->mWorldTransform);
	}
	else
	{
		mWorldTransform = mLocalTransform;
	}

	updateChildrenWorld();
}

void TransformComponent::updateChildrenWorld()
{
	for (auto child : mChildrenPtr)
	{
		child->updateWorld();
	}
}