#include "pch.h"

#include <MathUtil.h>
#include <Matrix4x4.h>
#include <Vector3.h>

#include "CameraComponent.h"
#include "TransformComponent.h"

std::list<CameraComponent*> CameraComponent::mContainerPtr;
std::list<CameraComponent*> CameraComponent::mEnabledTruePtr;
std::list<CameraComponent*> CameraComponent::mEnabledFalsePtr;
CameraComponent* CameraComponent::mCurrentCameraPtr = nullptr;

CameraComponent::CameraComponent()
	: BehaviourComponent(
		reinterpret_cast<std::list<BehaviourComponent*>*>(&mContainerPtr),
		reinterpret_cast<std::list<BehaviourComponent*>*>(&mEnabledTruePtr),
		reinterpret_cast<std::list<BehaviourComponent*>*>(&mEnabledFalsePtr))
	, mFov(60)
	, mNear(0.3f)
	, mFar(1000.f)
{
	// 나중에 삭제
	if (mCurrentCameraPtr == nullptr)
	{
		mCurrentCameraPtr = this;
	}
}

CameraComponent::~CameraComponent()
{
}

std::vector<CameraComponent*> CameraComponent::GetAllCameras()
{
	return std::vector<CameraComponent*>(mContainerPtr.begin(), mContainerPtr.end());
}

std::size_t CameraComponent::GetAllCamerasCount()
{
	return mContainerPtr.size();
}

CameraComponent* CameraComponent::GetMainCamera()
{
	for (auto camera : mContainerPtr)
	{
		if (camera->IsActiveAndEnabled())
		{
			if (camera->GetTag() == _T("MainCamera"))
			{
				return camera;
			}
		}
	}

	return nullptr;
}

CameraComponent* CameraComponent::GetCurrentCamera()
{
	return mCurrentCameraPtr;
}

int CameraComponent::GetFieldOfView() const
{
	return mFov;
}

float CameraComponent::GetNear() const
{
	return mNear;
}

float CameraComponent::GetFar() const
{
	return mFar;
}

void CameraComponent::SetFieldOfView(const int value)
{
	mFov = value;
}

void CameraComponent::SetNear(const float value)
{
	mNear = value;
}

void CameraComponent::SetFar(const float value)
{
	mFar = value;
}

const Matrix4x4 CameraComponent::GetViewMatrix()
{
	Matrix4x4 viewMat;
	Vector3 right = GetTransform()->GetLocalAxisX();
	Vector3 up = GetTransform()->GetLocalAxisY();
	Vector3 look = GetTransform()->GetLocalAxisZ();
	Vector3 pos = GetTransform()->GetPosition();

	float x = -Vector3::Dot(right, pos);
	float y = -Vector3::Dot(up, pos);
	float z = -Vector3::Dot(look, pos);

	viewMat(0, 0) = right.X; viewMat(0, 1) = up.X; viewMat(0, 2) = look.X; viewMat(0, 3) = 0.f;
	viewMat(1, 0) = right.Y; viewMat(1, 1) = up.Y; viewMat(1, 2) = look.Y; viewMat(1, 3) = 0.f;
	viewMat(2, 0) = right.Z; viewMat(2, 1) = up.Z; viewMat(2, 2) = look.Z; viewMat(2, 3) = 0.f;
	viewMat(3, 0) = x;       viewMat(3, 1) = y;    viewMat(3, 2) = z;      viewMat(3, 3) = 1.f;

	return viewMat;
}

const Matrix4x4 CameraComponent::GetProjectionMatrix(const int width, const int height)
{
	return Matrix4x4::Perspective(
		Math::Deg2Rad(static_cast<float>(mFov)),
		static_cast<float>(width) / static_cast<float>(height),
		mNear, mFar);
}

void CameraComponent::OnEnable()
{
	if (!mCurrentCameraPtr)
	{
		mCurrentCameraPtr = this;
	}
}

void CameraComponent::OnDisable()
{
	if (mCurrentCameraPtr == this)
	{
		if (!mEnabledTruePtr.empty())
		{
			mCurrentCameraPtr = mEnabledTruePtr.front();
		}
	}
}
