#pragma once

#include <string>
#include "stdafx.h"

#include "Component.h"

class TextComponent : public Component
{
public:
	using Component::Component;
	virtual ~TextComponent() noexcept = default;
	
	virtual void	Init() override;
	virtual void	Render() override;



	void			SetText(const wchar_t* text) noexcept;

	const wchar_t*			GetText() const noexcept;

	void			SetRect(RECT rect);
	void			SetBrush(float red, float blue, float green);
	void			SetIsKor(bool isKor);
	void			SetFontSize(int size);
private:

	const wchar_t* m_text = nullptr;
	
	IDWriteTextFormat* mp_textFormat = nullptr;
	ID2D1SolidColorBrush* m_brush = nullptr;
	RECT m_rect = {};
	bool mb_isKor = false;
	int m_fontSize = 20;
	
};