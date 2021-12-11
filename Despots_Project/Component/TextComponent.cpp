#include "TextComponent.h"
#include "../Manager/ImageManagerD2.h"

void TextComponent::Init()
{
	if (mb_isKor)
	{
		ImageManagerD2::GetInstance()->GetWriteFactory()->CreateTextFormat(
			L"Noto Sans CJK JP Regular",
			//L"±¼¸²",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			m_fontSize,
			L"ko",
			&mp_textFormat);
	}
	else
	{
		ImageManagerD2::GetInstance()->GetWriteFactory()->CreateTextFormat(
			L"Perfect DOS VGA 437",
			//L"±¼¸²",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			m_fontSize,
			L"en",
			&mp_textFormat);
	}

	mp_textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	mp_textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
}

void TextComponent::Render()
{
	
	ImageManagerD2::GetInstance()->GetRenderTarget()->DrawTextW(m_text, wcslen(m_text), mp_textFormat,
		D2D1::RectF(m_rect.left, m_rect.top, m_rect.right, m_rect.bottom), m_brush);	
}

void TextComponent::SetRect(RECT rect)
{
	m_rect = rect;
}

void TextComponent::SetBrush(float red, float blue, float green)
{
	ImageManagerD2::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(red / 255.0f, blue / 255.0f, green / 255.0f), &m_brush);
}

void TextComponent::SetIsKor(bool isKor)
{
	mb_isKor = isKor;
}

void TextComponent::SetFontSize(int size)
{
	m_fontSize = size;
}

void TextComponent::SetText(const wchar_t* text) noexcept
{
	m_text = text;
}

const wchar_t* TextComponent::GetText() const noexcept
{
	return m_text;
}
