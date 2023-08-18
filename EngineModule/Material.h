#pragma once

#include "Types.h"

struct Color;
class Texture;

class Material
{
public:
	Material(const std::wstring& name);
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

	Texture* mTexturePtr;
	eRenderingMode mRenderingMode;
};

