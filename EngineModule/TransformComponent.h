#pragma once

#include <Transform.h>

#include "Component.h"

class TransformComponent : public Component
{
public:
	TransformComponent();
	TransformComponent(const Transform& localTransform);

public: // 로컬 트랜스폼
	Vector3 GetLocalPosition() const;
	Quaternion GetLocalRotation() const;
	Vector3 GetLocalEulerAngles() const;
	Vector3 GetLocalScale() const;
	Vector3 GetLocalAxisX() const;
	Vector3 GetLocalAxisY() const;
	Vector3 GetLocalAxisZ() const;
	D3DXMATRIX GetLocalMatrix() const;

	void SetLocalPosition(const Vector3& position);
	void SetLocalRotation(const Quaternion& rotation);
	void SetLocalRotation(const Vector3& eulerAngles);
	void SetLocalScale(const Vector3& scale);

	void AddLocalPosition(const Vector3& position);
	void AddLocalRotation(const Vector3& eulerAngles);
	void AddLocalScale(const Vector3& scale);
	void AddLocalRotationX(const float degree);
	void AddLocalRotationY(const float degree);
	void AddLocalRotationZ(const float degree);

	void Translate(const Vector3& translation);

public: // 월드 트랜스폼
	Vector3 GetPosition() const;
	Quaternion GetRotation() const;
	Vector3 GetEulerAngles() const;
	Vector3 GetScale() const;
	Vector3 GetAxisX() const;
	Vector3 GetAxisY() const;
	Vector3 GetAxisZ() const;
	D3DXMATRIX GetMatrix() const;

	void SetPosition(const Vector3& position);
	void SetRotation(const Quaternion& rotation);
	void SetRotation(const Vector3& eulerAngles);
	void SetScale(const Vector3& scale);

	void AddPosition(const Vector3& position);
	void AddRotation(const Vector3& eulerAngles);
	void AddScale(const Vector3& scale);
	void AddRotationX(const float degree);
	void AddRotationY(const float degree);
	void AddRotationZ(const float degree);

public: // 계층관련
	TransformComponent* FindChild(const std::wstring& name);
	TransformComponent* GetChild(const std::size_t index);
	bool IsChildOf(const TransformComponent* const child);
	std::size_t GetChildCount();
	void DetachChildren();

	TransformComponent* GetRoot();

	bool HasParent();
	TransformComponent* GetParent();
	void SetParent(TransformComponent* const parent);

private:
	void removeFromParent();
	void updateLocal();
	void updateWorld();
	void updateChildrenWorld();

private:
	Transform mLocalTransform;
	Transform mWorldTransform;
	TransformComponent* mParentPtr;
	std::vector<TransformComponent*> mChildrenPtr;
};

