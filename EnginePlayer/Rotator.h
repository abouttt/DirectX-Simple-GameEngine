#pragma once

#include <CameraComponent.h>
#include <GameBehaviourComponent.h>

#include "Debug.h"

class Rotator : public GameBehaviourComponent
{
public:
	void Update() override
	{
		//float speed = 50 * GetTime().GetDeltaTime();
		//GetTransform().AddLocalRotation(Vector3(speed, speed, speed));
		GetTransform()->LookAt(CameraComponent::GetMainCamera()->GetTransform());
		Debug::Log(GetTransform()->GetEulerAngles());
	}

	void Start() override
	{
		Debug::Log(_T("Start"));
	}

	void OnEnable() override
	{
		GameBehaviourComponent::OnEnable();
		Debug::Log(_T("OnEnable"));
	}

	void OnDisable() override
	{
		GameBehaviourComponent::OnDisable();
		Debug::Log(_T("OnDisable"));
	}

	void OnDestroy() override
	{
		Debug::Log(_T("OnDestroy"));
	}
};

