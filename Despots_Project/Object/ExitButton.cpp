#include "ExitButton.h"
#include "stdafx.h"
#include "Component/ImageComponent.h"
#include "Component/ButtonComponent.h"
#include "Component/TextComponent.h"

void ExitButton::Init()
{
	SetRect({ (WIN_SIZE_X / 2) + 100, (WIN_SIZE_Y / 2) + 200, (WIN_SIZE_X / 2) + 350, (WIN_SIZE_Y / 2) + 300 });

	m_hoverImg = new ImageComponent(this, 1);
	m_hoverImg->SetImage(L"Image/Title/Exit_Hover.png");
	m_hoverImg->SetRect(GetRect());
	m_hoverImg->SetIsVisible(false);

	m_clickImg = new ImageComponent(this, 2);
	m_clickImg->SetImage(L"Image/Title/Exit_Active.png");
	m_clickImg->SetRect(GetRect());
	m_clickImg->SetIsVisible(false);

	m_buttonComp = new ButtonComponent(this, 3, this, &ExitButton::GameExit);
	m_buttonComp->SetCollisionRect(GetRect());

	m_textComp = new TextComponent(this, 4);
	m_textComp->SetText(L"³¡³»±â");
	m_textComp->SetRect(GetRect());
	m_textComp->SetBrush(111, 107, 128);
	m_textComp->SetFontSize(40);
	m_textComp->SetIsKor(true);

	GameObject::Init();
}

void ExitButton::Update()
{
	GameObject::Update();
	switch (m_buttonComp->GetButtonState())
	{
	case eButtonState::Idle:
		m_textComp->SetBrush(111, 107, 128);
		m_hoverImg->SetIsVisible(false);
		m_clickImg->SetIsVisible(false);
		break;
	case eButtonState::Hover:
		m_textComp->SetBrush(184, 60, 102);
		m_hoverImg->SetIsVisible(true);
		m_clickImg->SetIsVisible(false);
		break;
	case eButtonState::Click:
		m_textComp->SetBrush(28, 18, 32);
		m_hoverImg->SetIsVisible(false);
		m_clickImg->SetIsVisible(true);
		break;
	default:
		break;
	}
}

void ExitButton::GameExit()
{
	PostQuitMessage(0);
}
