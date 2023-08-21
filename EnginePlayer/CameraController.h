#pragma once

#include "CameraComponent.h"
#include "GameBehaviourComponent.h"
#include "SoundComponent.h"
#include "Rotator.h"

class CameraController : public GameBehaviourComponent
{
	void Start() override
	{
		mCameraPtr = CameraComponent::GetCurrentCamera();
		mCube = GetScene().FindComponent<Rotator>();
		mSound = GetScene().FindComponent<SoundComponent>();
	}

	void Update() override
	{
		if (GetInput().GetKeyDown(eKeyCode::Space))
		{
			mCube->SetActive(!mCube->IsActive());
			//mCube->SetEnabled(!mCube->IsEnabled());
			//GetScene()->RemoveGameObject(cube->GetGameObject());
			//cube->GetGameObject()->RemoveComponent(cube);
			//GetScene().RemoveGameObject(cube->GetGameObject());
			mSound->Play();
		}
		
		if (GetInput().GetKey(eKeyCode::W))
		{
			mCameraPtr->GetTransform()->Translate(Vector3(0, 0, mSpeed * GetTime().GetDeltaTime()));
		}
		if (GetInput().GetKey(eKeyCode::S))
		{
			mCameraPtr->GetTransform()->Translate(Vector3(0, 0, -mSpeed * GetTime().GetDeltaTime()));
		}
		if (GetInput().GetKey(eKeyCode::A))
		{
			mCameraPtr->GetTransform()->Translate(Vector3(-mSpeed * GetTime().GetDeltaTime(), 0, 0));
		}
		if (GetInput().GetKey(eKeyCode::D))
		{
			mCameraPtr->GetTransform()->Translate(Vector3(mSpeed * GetTime().GetDeltaTime(), 0, 0));
		}
		if (GetInput().GetKey(eKeyCode::R))
		{
			mCameraPtr->GetTransform()->AddPosition(Vector3(0, mSpeed * GetTime().GetDeltaTime(), 0));
		}
		if (GetInput().GetKey(eKeyCode::F))
		{
			mCameraPtr->GetTransform()->AddPosition(Vector3(0, -mSpeed * GetTime().GetDeltaTime(), 0));
		}

		float x = GetInput().GetAxisMouseY() * 0.2f;
		float y = GetInput().GetAxisMouseX() * 0.2f;
		mCameraPtr->GetTransform()->AddRotationX(GetInput().GetAxisMouseY() * 0.2f);
		mCameraPtr->GetTransform()->AddRotationY(GetInput().GetAxisMouseX() * 0.2f);
	}

	void LateUpdate() override
	{
		//Debug::Log(GetTransform()->GetPosition());
	}

private:
	CameraComponent* mCameraPtr = nullptr;
	float mSpeed = 50;
	Rotator* mCube;
	SoundComponent* mSound;
};

