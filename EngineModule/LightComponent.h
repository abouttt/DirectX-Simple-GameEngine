#pragma once

#include "BehaviourComponent.h"

struct Color;
enum class eLightType;

class LightComponent : public BehaviourComponent
{
public:
	friend class RenderManager;

public:
	LightComponent(const eLightType lightType);
	~LightComponent();

public:
	void SetLightType(const eLightType lightType);
	void SetColor(const Color& color);
	void SetRange(const float range);

protected:
	void OnEnable() override;
	void OnDisable() override;

private:
	void initDirectionLight();
	void initPointLight();
	void initSpotLight();
	void updatePositionAndDirection();

private:
	static std::list<LightComponent*> mContainerPtr;
	static std::list<LightComponent*> mEnabledTruePtr;
	static std::list<LightComponent*> mEnabledFalsePtr;
	static DWORD mLightCount;

	D3DLIGHT9 mNativeLight;
	DWORD mIndex;
};

