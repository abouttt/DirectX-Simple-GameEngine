#include "pch.h"

#include <MathUtil.h>
#include <Vector3.h>

#include "CameraComponent.h"
#include "TransformComponent.h"

std::vector<CameraComponent*> CameraComponent::mAllCamerasPtr;
CameraComponent* CameraComponent::mCurrentCameraPtr = nullptr;

CameraComponent::CameraComponent()
	: mFov(60)
	, mNear(0.3f)
	, mFar(1000.f)
	, mViewMat()
	, mProjMat()
{
	mAllCamerasPtr.emplace_back(this);
}

CameraComponent::~CameraComponent()
{
	mAllCamerasPtr.erase(std::find(mAllCamerasPtr.begin(), mAllCamerasPtr.end(), this));
}

std::vector<CameraComponent*> CameraComponent::GetAllCameras()
{
	return mAllCamerasPtr;
}

std::size_t CameraComponent::GetAllCamerasCount()
{
	return mAllCamerasPtr.size();
}

CameraComponent* CameraComponent::GetMainCamera()
{
	for (auto camera : mAllCamerasPtr)
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

const D3DXMATRIX& CameraComponent::GetViewMatrix()
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

const D3DXMATRIX& CameraComponent::GetProjectionMatrix(const int width, const int height)
{
	D3DXMatrixPerspectiveFovLH(
		&mProjMat,
		Math::Deg2Rad(static_cast<float>(mFov)),
		static_cast<float>(width) / static_cast<float>(height),
		mNear,
		mFar);

	return mProjMat;
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
	if (this == mCurrentCameraPtr)
	{
		for (auto camera : mAllCamerasPtr)
		{
			if (camera->IsActiveAndEnabled())
			{
				mCurrentCameraPtr = camera;
				break;
			}
		}
	}
}
