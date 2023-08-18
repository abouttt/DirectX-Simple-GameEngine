#include "pch.h"
#include "Color.h"
#include "EngineUtil.h"
#include "Material.h"

Material::Material(const std::wstring& name)
	: mName(name)
	, mNativeMaterial(engineutil::WHITE_MTRL)
	, mTexturePtr(nullptr)
	, mRenderingMode(eRenderingMode::Opaque)
{
}

Material::~Material()
{
	mTexturePtr = nullptr;
}

const std::wstring& Material::GetName() const
{
	return mName;
}

D3DMATERIAL9& Material::GetNativeMaterial()
{
	return mNativeMaterial;
}

Texture* Material::GetTexture()
{
	return mTexturePtr;
}

const Color& Material::GetColor() const
{
	return Diffuse;
}

eRenderingMode Material::GetRenderingMode() const
{
	return mRenderingMode;
}

void Material::SetTexture(Texture* const texture)
{
	mTexturePtr = texture;
}

void Material::SetColor(const Color& color)
{
	Diffuse = color;
	Ambient = color;
	Specular = color;
	Emissive = Color::Black;
	Power = 8.f;
}

void Material::SetAlpha(const float alpha)
{
	Diffuse.A = std::clamp(alpha, 0.f, 1.f);
}

void Material::SetRenderingMode(const eRenderingMode mode)
{
	mRenderingMode = mode;
}
