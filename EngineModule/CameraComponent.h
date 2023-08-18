#pragma once

#include "BehaviorComponent.h"

struct Matrix4x4;

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

	const Matrix4x4 GetViewMatrix();
	const Matrix4x4 GetProjectionMatrix(const int width, const int height);

protected:
	void OnEnable() override;
	void OnDisable() override;

private:
	static std::vector<CameraComponent*> mContainerPtr;
	static CameraComponent* mCurrentCameraPtr;

	int mFov;
	float mNear;
	float mFar;
};

