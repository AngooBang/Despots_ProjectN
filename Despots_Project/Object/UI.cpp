#include "UI.h"
#include "Component/ImageComponent.h"

void UI::Init()
{
	m_uiImg = new ImageComponent(this, 1);
	m_uiImg->SetImage(L"Image/UI/UI.png");
	m_uiImg->SetIsCam(false);
	m_uiImg->SetRect({0, 0, 350, 70});

	m_minimapImg = new ImageComponent(this, 1);
	m_minimapImg->SetImage(L"Image/UI/mini_01.png");
	m_minimapImg->SetIsCam(false);
	m_minimapImg->SetRect({ 10, 70, 120, 180 });
}

void UI::SetMinimapImg(const wchar_t* path)
{
	m_minimapImg->SetImage(path);
}
