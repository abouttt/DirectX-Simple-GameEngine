#include "pch.h"
#include "EngineUtil.h"
#include "TransformComponent.h"
#include "TextComponent.h"

TextComponent::TextComponent()
	: mNativeFont()
	, mTextString()
	, mDesc()
	, mColor(Color::Black)
	, mFlag(DT_LEFT)
{
}

TextComponent::~TextComponent()
{
	if (mNativeFont)
	{
		mNativeFont->Release();
	}
}

void TextComponent::SetSize(const UINT size)
{
	mDesc.Height = size;
}

void TextComponent::SetItalic(const bool bItalic)
{
	mDesc.Italic = bItalic;
}

void TextComponent::SetColor(const Color& color)
{
	mColor = color;
}

void TextComponent::SetFlag(const DWORD flag)
{
	mFlag = flag;
}

void TextComponent::SetFont(const std::wstring& fontName)
{
	wcscpy(mDesc.FaceName, fontName.c_str());
}

void TextComponent::SetText(const std::wstring& text)
{
	mTextString = text;
}

void TextComponent::Draw(IDirect3DDevice9* const device)
{
	if (!mNativeFont && !init(device))
	{
		return;
	}

	auto position = GetTransform()->GetPosition().NativeVector3;
	RECT rect{};
	rect.left = static_cast<LONG>(position.x);
	rect.top = static_cast<LONG>(position.y);
	mNativeFont->DrawText(nullptr, mTextString.c_str(), static_cast<int>(mTextString.size()), &rect, DT_NOCLIP | mFlag, mColor);
}

bool TextComponent::init(IDirect3DDevice9* const device)
{
	::ZeroMemory(&mDesc, sizeof(D3DXFONT_DESC));
	mDesc.Width = 0;
	mDesc.Height = 30;
	mDesc.Weight = FW_NORMAL;
	mDesc.MipLevels = 1;
	mDesc.Italic = false;
	mDesc.CharSet = HANGUL_CHARSET;
	mDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
	mDesc.Quality = DEFAULT_QUALITY;
	mDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	wcscpy(mDesc.FaceName, _T("±¼¸²"));

	if (FAILED(D3DXCreateFontIndirect(device, &mDesc, &mNativeFont)))
	{
		::MessageBox(nullptr, _T("Text/init/D3DXCreateFontIndirect : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	return true;
}
