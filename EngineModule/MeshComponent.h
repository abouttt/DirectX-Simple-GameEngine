#pragma once

#include "BehaviourComponent.h"

class Mesh;
class Material;

class MeshComponent : public BehaviourComponent
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
	static std::vector<MeshComponent*> mAllContainerPtr;
	static std::vector<MeshComponent*> mTrueContainerPtr;
	static std::vector<MeshComponent*> mFalseContainerPtr;

	Mesh* mMeshPtr;
	Material* mMaterialPtr;
};

