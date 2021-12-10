#include "StartButton.h"
#include "stdafx.h"
#include "../Manager/SceneManager.h"
#include "Component/ImageComponent.h"
#include "Component/ButtonComponent.h"

void StartButton::Init()
{
	SetRect({ 100, 500, 300, 580 });

	m_hoverImg = new ImageComponent(this, 1);
	m_hoverImg->SetImage(L"Image/Title/Start_Hover.png");
	m_hoverImg->SetRect(GetRect());
	m_hoverImg->SetIsVisible(false);

	m_clickImg = new ImageComponent(this, 2);
	m_clickImg->SetImage(L"Image/Title/Start_Active.png");
	m_clickImg->SetRect(GetRect());
	m_clickImg->SetIsVisible(false);

	m_buttonComp = new ButtonComponent(this, 3, this, &StartButton::GameStart);
	m_buttonComp->SetCollisionRect(GetRect());
}

void StartButton::Update()
{
	GameObject::Update();
	switch (m_buttonComp->GetButtonState())
	{
	case eButtonState::Idle:
		m_hoverImg->SetIsVisible(false);
		m_clickImg->SetIsVisible(false);
		break;
	case eButtonState::Hover:
		m_hoverImg->SetIsVisible(true);
		m_clickImg->SetIsVisible(false);
		break;
	case eButtonState::Click:
		m_hoverImg->SetIsVisible(false);
		m_clickImg->SetIsVisible(true);
		break;
	default:
		break;
	}
}

void StartButton::GameStart()
{
	SceneManager::GetInstance()->SetNextScene(L"Game");
	SceneManager::GetInstance()->ChangeScene();
}
