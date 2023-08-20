#pragma once

#include "CameraComponent.h"
#include "GameBehaviourComponent.h"
#include "Rotator.h"

class CameraController : public GameBehaviourComponent
{
	void Start() override
	{
		mCameraPtr = CameraComponent::GetCurrentCamera();
		cube = GetScene().FindGameObject(_T("Cube"))->GetComponent<Rotator>();
	}

	void Update() override
	{
		if (GetInput().GetKeyDown(KeyCode::Space))
		{
			//cube->SetActive(!cube->IsActive());
			//cube->SetEnabled(!cube->IsEnabled());
			//GetScene()->RemoveGameObject(cube->GetGameObject());
			//cube->GetGameObject()->RemoveComponent(cube);
			//GetScene().RemoveGameObject(cube->GetGameObject());
		}
		
		if (GetInput().GetKey(KeyCode::W))
		{
			mCameraPtr->GetTransform()->Translate(Vector3(0, 0, mSpeed * GetTime().GetDeltaTime()));
		}
		if (GetInput().GetKey(KeyCode::S))
		{
			mCameraPtr->GetTransform()->Translate(Vector3(0, 0, -mSpeed * GetTime().GetDeltaTime()));
		}
		if (GetInput().GetKey(KeyCode::A))
		{
			mCameraPtr->GetTransform()->Translate(Vector3(-mSpeed * GetTime().GetDeltaTime(), 0, 0));
		}
		if (GetInput().GetKey(KeyCode::D))
		{
			mCameraPtr->GetTransform()->Translate(Vector3(mSpeed * GetTime().GetDeltaTime(), 0, 0));
		}
		if (GetInput().GetKey(KeyCode::R))
		{
			mCameraPtr->GetTransform()->AddPosition(Vector3(0, mSpeed * GetTime().GetDeltaTime(), 0));
		}
		if (GetInput().GetKey(KeyCode::F))
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
	Rotator* cube;
};

