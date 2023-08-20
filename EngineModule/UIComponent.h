#pragma once

#include "BehaviourComponent.h"

class UIComponent : public BehaviourComponent
{
public:
	friend class RenderManager;

public:
	UIComponent();
	virtual ~UIComponent();

protected:
	void OnEnable() override;
	void OnDisable() override;

public:
	virtual void Draw(IDirect3DDevice9* const device) abstract;

private:
	static std::list<UIComponent*> mAllContainerPtr;
	static std::list<UIComponent*> mTrueContainerPtr;
	static std::list<UIComponent*> mFalseContainerPtr;
};

