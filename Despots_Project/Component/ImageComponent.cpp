#include "ImageComponent.h"
#include "stdafx.h"
#include "Util/Image2D.h"

void ImageComponent::Render()
{
	m_img->Render(m_rect);
}

void ImageComponent::SetImage(const wchar_t* path)
{
	m_img = FIND_IMG(path);
}

void ImageComponent::SetRect(RECT rect)
{
	m_rect = rect;
}
