#include "ImageComponent.h"
#include "stdafx.h"
#include "Util/Image2D.h"

void ImageComponent::Render()
{
	if (!mb_isVisible) return;

	m_img->Render(m_rect);
}

int ImageComponent::GetWidth()
{
	return m_img->GetWidth();
}

int ImageComponent::GetHeight()
{
	return m_img->GetHeight();
}

void ImageComponent::SetImage(const wchar_t* path)
{
	m_img = FIND_IMG(path);
}

void ImageComponent::SetRect(RECT rect)
{
	m_rect = rect;
}

void ImageComponent::SetIsVisible(bool isVisible)
{
	mb_isVisible = isVisible;
}
