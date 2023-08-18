#pragma once

class Material;
class Mesh;
class Texture;
enum class eRenderingMode;

class ResourceManager
{
public:
	friend class GameEngine;

public:
	ResourceManager();
	~ResourceManager();

public:
	Material* GetMaterial(const std::wstring& name);
	Mesh* GetMesh(const std::wstring& name);
	Texture* GetTexture(const std::wstring& name);

	bool CreateAndAddMaterial(const std::wstring& name, const eRenderingMode mode, const D3DMATERIAL9& nativeMaterial, Texture* const texture);
	bool CreateAndAddNativeMesh(const std::wstring& name, ID3DXMesh* const nativeMesh);
	bool LoadTexture(const std::wstring& name, const std::wstring& path);

private:
	bool init(IDirect3DDevice9* const device);

private:
	bool mbInit;
	IDirect3DDevice9* mDevicePtr;
	std::unordered_map<std::wstring, std::unique_ptr<Material>> mMaterials;
	std::unordered_map<std::wstring, std::unique_ptr<Mesh>> mMeshes;
	std::unordered_map<std::wstring, std::unique_ptr<Texture>> mTextures;
};

