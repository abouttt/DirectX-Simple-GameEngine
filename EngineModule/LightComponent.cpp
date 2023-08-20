#include "pch.h"

#include <Quaternion.h>

#include "Color.h"
#include "LightComponent.h"
#include "TransformComponent.h"
#include "Types.h"

std::list<LightComponent*> LightComponent::mAllContainerPtr;
std::list<LightComponent*> LightComponent::mTrueContainerPtr;
std::list<LightComponent*> LightComponent::mFalseContainerPtr;
DWORD LightComponent::mLightCount = 0;

LightComponent::LightComponent(const eLightType lightType)
	: BehaviourComponent(reinterpret_cast<std::list<BehaviourComponent*>&>(mAllContainerPtr))
	, mNativeLight()
	, mIndex(mLightCount++)
{
	SetLightType(lightType);
	SetColor(Color::White);
	OnEnable();
}

LightComponent::~LightComponent()
{
	RemoveThisAllContainer(
		reinterpret_cast<std::list<BehaviourComponent*>&>(mAllContainerPtr),
		reinterpret_cast<std::list<BehaviourComponent*>&>(mTrueContainerPtr),
		reinterpret_cast<std::list<BehaviourComponent*>&>(mFalseContainerPtr));
}

void LightComponent::SetLightType(const eLightType lightType)
{
	::ZeroMemory(&mNativeLight, sizeof(D3DLIGHT9));
	switch (lightType)
	{
	case eLightType::Directional:
		initDirectionLight();
		break;
	case eLightType::Point:
		initPointLight();
		break;
	case eLightType::Spot:
		initSpotLight();
		break;
	}
}

void LightComponent::SetColor(const Color& color)
{
	D3DXCOLOR adjustColor = color.NativeColor * 0.6f;
	mNativeLight.Ambient = adjustColor;
	mNativeLight.Diffuse = color.NativeColor;
	mNativeLight.Specular = adjustColor;
}

void LightComponent::SetRange(const float range)
{
	mNativeLight.Range = range;
}

void LightComponent::OnEnable()
{
	InAndOutContainer(reinterpret_cast<std::list<BehaviourComponent*>&>(mTrueContainerPtr),
		reinterpret_cast<std::list<BehaviourComponent*>&>(mFalseContainerPtr));
}

void LightComponent::OnDisable()
{
	InAndOutContainer(reinterpret_cast<std::list<BehaviourComponent*>&>(mFalseContainerPtr),
		reinterpret_cast<std::list<BehaviourComponent*>&>(mTrueContainerPtr));
}

void LightComponent::initDirectionLight()
{
	mNativeLight.Type = D3DLIGHT_DIRECTIONAL;
}

void LightComponent::initPointLight()
{
	mNativeLight.Type = D3DLIGHT_POINT;
	mNativeLight.Range = 1000.0f;
	mNativeLight.Falloff = 1.0f;
	mNativeLight.Attenuation0 = 1.0f;
	mNativeLight.Attenuation1 = 0.0f;
	mNativeLight.Attenuation2 = 0.0f;
}

void LightComponent::initSpotLight()
{
	mNativeLight.Type = D3DLIGHT_SPOT;
	mNativeLight.Range = 1000.0f;
	mNativeLight.Falloff = 1.0f;
	mNativeLight.Attenuation0 = 1.0f;
	mNativeLight.Attenuation1 = 0.0f;
	mNativeLight.Attenuation2 = 0.0f;
	mNativeLight.Theta = 0.5f;
	mNativeLight.Phi = 0.7f;
}

void LightComponent::updatePositionAndDirection()
{
	mNativeLight.Position = GetTransform()->GetPosition().NativeVector3;
	D3DXQUATERNION rotation = GetTransform()->GetRotation().NativeQuaternion;
	D3DXVECTOR3 axis;
	float angle;
	D3DXQuaternionToAxisAngle(&rotation, &axis, &angle);
	D3DXVec3Normalize(static_cast<D3DXVECTOR3*>(&mNativeLight.Direction), &axis);
}
