#pragma once

#include "Color.h"
#include "Types.h"

class Texture;

class Material
{
public:
	Material(const std::wstring& name);
	Material(const std::wstring& name, const eRenderingMode mode, const D3DMATERIAL9& nativeMaterial, Texture* const texture);
	~Material();

public:
	const std::wstring& GetName() const;
	D3DMATERIAL9& GetNativeMaterial();
	Texture* GetTexture();
	const Color& GetColor() const;
	eRenderingMode GetRenderingMode() const;

	void SetTexture(Texture* const texture);
	void SetColor(const Color& color);
	void SetAlpha(const float alpha);
	void SetRenderingMode(const eRenderingMode mode);

private:
	std::wstring mName;
	eRenderingMode mRenderingMode;
	Texture* mTexturePtr;
	union
	{
		struct
		{
			Color Diffuse;
			Color Ambient;
			Color Specular;
			Color Emissive;
			float Power;
		};

		D3DMATERIAL9 mNativeMaterial;
	};
};

