#pragma once

#include "BehaviorComponent.h"

class Mesh;
class Material;

class MeshComponent : public BehaviorComponent
{
public:
	friend class RenderManager;

public:
	MeshComponent();
	MeshComponent(Mesh* const mesh);
	MeshComponent(Mesh* const mesh, Material* const material);
	~MeshComponent();

public:
	Mesh* GetMesh();
	Material* GetMaterial();

	void SetMesh(Mesh* const mesh);
	void SetMaterial(Material* const material);

protected:
	void OnEnable() override;
	void OnDisable() override;

private:
	void render(IDirect3DDevice9* const device);

private:
	static std::list<MeshComponent*> mContainerPtr;
	static std::list<MeshComponent*> mEnabledTruePtr;
	static std::list<MeshComponent*> mEnabledFalsePtr;

	Mesh* mMeshPtr;
	Material* mMaterialPtr;
};

