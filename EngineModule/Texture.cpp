#include "pch.h"
#include "Texture.h"

Texture::Texture(const std::wstring* name, IDirect3DTexture9* const nativeTexture)
	: mName(name)
	, mNativeTexture(nativeTexture)
	, mDesc()
{
	::ZeroMemory(&mDesc, sizeof(mDesc));
	mNativeTexture->GetLevelDesc(0, &mDesc);
}

Texture::~Texture()
{
	if (mNativeTexture)
	{
		mNativeTexture->Release();
		mNativeTexture = nullptr;
	}
}

const std::wstring& Texture::GetName() const
{
	return *mName;
}

unsigned int Texture::GetWidth() const
{
	return mDesc.Width;
}

unsigned int Texture::GetHeight() const
{
	return mDesc.Height;
}

IDirect3DTexture9* Texture::GetNativeTexture()
{
	return mNativeTexture;
}
