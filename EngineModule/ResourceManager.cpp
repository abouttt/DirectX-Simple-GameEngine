#include "pch.h"
#include "Material.h"
#include "Mesh.h"
#include "ResourceManager.h"
#include "Texture.h"

ResourceManager::ResourceManager()
	: mbInit(false)
	, mDevicePtr(nullptr)
	, mMaterials()
	, mMeshes()
	, mTextures()
{
}

ResourceManager::~ResourceManager()
{
	mDevicePtr = nullptr;
	mbInit = false;
}

Material* ResourceManager::GetMaterial(const std::wstring& name)
{
	auto it = mMaterials.find(name);
	return it != mMaterials.end() ? it->second.get() : nullptr;
}

Mesh* ResourceManager::GetMesh(const std::wstring& name)
{
	auto it = mMeshes.find(name);
	return it != mMeshes.end() ? it->second.get() : nullptr;
}

Texture* ResourceManager::GetTexture(const std::wstring& name)
{
	auto it = mTextures.find(name);
	return it != mTextures.end() ? it->second.get() : nullptr;
}

bool ResourceManager::CreateAndAddMaterial(const std::wstring& name, const eRenderingMode mode, const D3DMATERIAL9& nativeMaterial, Texture* const texture)
{
	if (mMaterials.find(name) != mMaterials.end())
	{
		return false;
	}

	mMaterials[name] = std::make_unique<Material>(name, mode, nativeMaterial, texture);
	return true;
}

bool ResourceManager::CreateAndAddNativeMesh(const std::wstring& name, ID3DXMesh* const nativeMesh)
{
	if (mMeshes.find(name) != mMeshes.end())
	{
		return false;
	}

	mMeshes[name] = std::make_unique<Mesh>(name, nativeMesh);
	return true;
}

bool ResourceManager::LoadTexture(const std::wstring& name, const std::wstring& path)
{
	if (mTextures.find(name) != mTextures.end())
	{
		return false;
	}

	IDirect3DTexture9* nativeTexture = nullptr;
	HRESULT hr = D3DXCreateTextureFromFile(mDevicePtr, (_T("../Resources/") + path).c_str(), &nativeTexture);

	if (FAILED(hr))
	{
		return false;
	}

	mTextures[name] = std::make_unique<Texture>(name, nativeTexture);
	return true;
}

bool ResourceManager::init(IDirect3DDevice9* const device)
{
	mDevicePtr = device;

	if (mbInit)
	{
		return false;
	}

	// TODO : Resources 폴더에서 자동으로 바인딩 작업.

	mbInit = true;
	return true;
}
