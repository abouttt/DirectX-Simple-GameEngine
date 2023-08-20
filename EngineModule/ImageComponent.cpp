#include "pch.h"

#include <Matrix4x4.h>
#include <Vector3.h>

#include "EngineUtil.h"
#include "ImageComponent.h"
#include "Texture.h"
#include "TransformComponent.h"

ImageComponent::ImageComponent()
	: mSprite(nullptr)
	, mTexture(nullptr)
	, mColor(Color::White)
{
}

ImageComponent::~ImageComponent()
{
	if (mSprite)
	{
		mSprite->Release();
	}
}

Texture* ImageComponent::GetTexture() const
{
	return mTexture;
}

void ImageComponent::SetTexture(Texture* const texture)
{
	mTexture = texture;
}

void ImageComponent::SetColor(const Color& color)
{
	mColor = color;
}

void ImageComponent::Draw(IDirect3DDevice9* const device)
{
	if (!mSprite && !init(device))
	{
		return;
	}

	auto position = GetTransform()->GetPosition().NativeVector3;
	auto matrix = GetTransform()->GetMatrix().NativeMatrix;

	mSprite->SetTransform(&matrix);
	mSprite->Begin(D3DXSPRITE_ALPHABLEND);
	mSprite->Draw(mTexture->GetNativeTexture(), nullptr, nullptr, &position, mColor);
	mSprite->End();
}

bool ImageComponent::init(IDirect3DDevice9* const device)
{
	if (FAILED(D3DXCreateSprite(device, &mSprite)))
	{
		::MessageBox(nullptr, _T("ImageComponent - init()/D3DXCreateSprite() : FAILED"), 0, 0);
		return false;
	}

	return true;
}
