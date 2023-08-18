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
	static std::vector<LightComponent*> mAllContainerPtr;
	static std::vector<LightComponent*> mTrueContainerPtr;
	static std::vector<LightComponent*> mFalseContainerPtr;
	static DWORD mLightCount;

	D3DLIGHT9 mNativeLight;
	DWORD mIndex;
};

