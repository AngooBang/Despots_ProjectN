#include "TextComponent.h"

#include "../Object/GameObject.h"

void TextComponent::Render()
{

}

void TextComponent::SetText(const std::wstring& text) noexcept
{
	_text = text;
}

std::wstring TextComponent::GetText() const noexcept
{
	return _text;
}
