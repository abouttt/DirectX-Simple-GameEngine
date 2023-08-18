#pragma once

class Texture
{
public:
	Texture(const std::wstring& name, IDirect3DTexture9* const nativeTexture);
	~Texture();

public:
	const std::wstring& GetName() const;
	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	IDirect3DTexture9* GetNativeTexture();

private:
	std::wstring mName;
	IDirect3DTexture9* mNativeTexture;
	D3DSURFACE_DESC mDesc;
};

