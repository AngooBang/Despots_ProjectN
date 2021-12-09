#include "RectComponent.h"
#include "../Object/GameObject.h"

void RectComponent::Render()
{

}

void RectComponent::SetPen(COLORREF color) noexcept
{
	_pen = CreatePen(PS_SOLID, 1, color);
}

void RectComponent::SetBrush(COLORREF color) noexcept
{
	_brush = CreateSolidBrush(color);
}
