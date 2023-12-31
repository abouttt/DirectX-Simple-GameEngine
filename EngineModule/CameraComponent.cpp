#include "pch.h"

#include <MathUtil.h>
#include <Vector3.h>

#include "CameraComponent.h"
#include "TransformComponent.h"

std::vector<CameraComponent*> CameraComponent::mAllContainerPtr;
std::vector<CameraComponent*> CameraComponent::mTrueContainerPtr;
std::vector<CameraComponent*> CameraComponent::mFalseContainerPtr;
CameraComponent* CameraComponent::mCurrentCameraPtr = nullptr;

CameraComponent::CameraComponent()
	: BehaviourComponent(reinterpret_cast<std::vector<BehaviourComponent*>&>(mAllContainerPtr))
	, mFov(60)
	, mNear(0.3f)
	, mFar(1000.f)
	, mViewMat()
	, mProjMat()
{
}

CameraComponent::~CameraComponent()
{
	RemoveThisAllContainer(
		reinterpret_cast<std::vector<BehaviourComponent*>&>(mAllContainerPtr),
		reinterpret_cast<std::vector<BehaviourComponent*>&>(mTrueContainerPtr),
		reinterpret_cast<std::vector<BehaviourComponent*>&>(mFalseContainerPtr));
}

std::vector<CameraComponent*> CameraComponent::GetAllCameras()
{
	return std::vector<CameraComponent*>(mAllContainerPtr.begin(), mAllContainerPtr.end());
}

std::size_t CameraComponent::GetAllCamerasCount()
{
	return mAllContainerPtr.size();
}

CameraComponent* CameraComponent::GetMainCamera()
{
	for (auto camera : mTrueContainerPtr)
	{
		if (camera->IsActive())
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

const Matrix4x4& CameraComponent::GetViewMatrix()
{
	Vector3 right = GetTransform()->GetLocalAxisX();
	Vector3 up = GetTransform()->GetLocalAxisY();
	Vector3 look = GetTransform()->GetLocalAxisZ();
	Vector3 pos = GetTransform()->GetPosition();

	float x = -Vector3::Dot(right, pos);
	float y = -Vector3::Dot(up, pos);
	float z = -Vector3::Dot(look, pos);

	mViewMat(0, 0) = right.X; mViewMat(0, 1) = up.X; mViewMat(0, 2) = look.X; mViewMat(0, 3) = 0.f;
	mViewMat(1, 0) = right.Y; mViewMat(1, 1) = up.Y; mViewMat(1, 2) = look.Y; mViewMat(1, 3) = 0.f;
	mViewMat(2, 0) = right.Z; mViewMat(2, 1) = up.Z; mViewMat(2, 2) = look.Z; mViewMat(2, 3) = 0.f;
	mViewMat(3, 0) = x;       mViewMat(3, 1) = y;    mViewMat(3, 2) = z;      mViewMat(3, 3) = 1.f;

	return mViewMat;
}

const Matrix4x4& CameraComponent::GetProjectionMatrix(const int width, const int height)
{
	mProjMat.SetPerspective(Math::Deg2Rad(static_cast<float>(mFov)),
		static_cast<float>(width) / static_cast<float>(height),
		mNear, mFar);
	
	return mProjMat;
}

void CameraComponent::OnEnable()
{
	InAndOutContainer(reinterpret_cast<std::vector<BehaviourComponent*>&>(mTrueContainerPtr),
		reinterpret_cast<std::vector<BehaviourComponent*>&>(mFalseContainerPtr));

	if (!mCurrentCameraPtr)
	{
		mCurrentCameraPtr = this;
	}
}

void CameraComponent::OnDisable()
{
	InAndOutContainer(reinterpret_cast<std::vector<BehaviourComponent*>&>(mFalseContainerPtr),
		reinterpret_cast<std::vector<BehaviourComponent*>&>(mTrueContainerPtr));

	if (mCurrentCameraPtr == this)
	{
		if (!mTrueContainerPtr.empty())
		{
			mCurrentCameraPtr = mTrueContainerPtr.front();
		}
	}
}
