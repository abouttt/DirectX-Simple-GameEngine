#pragma once

#include "Color.h"
#include "UIComponent.h"

class Texture;

class ImageComponent : public UIComponent
{
public:
	ImageComponent();
	~ImageComponent();

public:
	Texture* GetTexture() const;
	void SetTexture(Texture* const texture);
	void SetColor(const Color& color);

	void Draw(IDirect3DDevice9* const device) override;

private:
	bool init(IDirect3DDevice9* const device);

private:
	ID3DXSprite* mSprite;
	Texture* mTexture;
	Color mColor;
};

