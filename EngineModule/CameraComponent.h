#pragma once

#include "BehaviorComponent.h"

class CameraComponent : public BehaviorComponent
{
public:
	CameraComponent();
	~CameraComponent();

public:
	static std::vector<CameraComponent*> GetAllCameras();
	static std::size_t GetAllCamerasCount();
	static CameraComponent* GetMainCamera();
	static CameraComponent* GetCurrentCamera();

public:
	int GetFieldOfView() const;
	float GetNear() const;
	float GetFar() const;

	void SetFieldOfView(const int value);
	void SetNear(const float value);
	void SetFar(const float value);

	const D3DXMATRIX& GetViewMatrix();
	const D3DXMATRIX& GetProjectionMatrix(const int width, const int height);

protected:
	void OnEnable() override;
	void OnDisable() override;

private:
	static std::vector<CameraComponent*> mAllCamerasPtr;
	static CameraComponent* mCurrentCameraPtr;

	int mFov;
	float mNear;
	float mFar;
	D3DXMATRIX mViewMat;
	D3DXMATRIX mProjMat;
};

