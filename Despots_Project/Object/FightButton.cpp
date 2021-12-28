#include "FightButton.h"
#include "Component/ImageComponent.h"
#include "Component/ButtonComponent.h"
#include "Manager/GameManager.h"

void FightButton::Init()
{
	SetPosition({ FIGHTBTN_POS_X, FIGHTBTN_POS_Y });

	SetRect({ GetPosition().x - FIGHTBTN_SIZE_X / 2, GetPosition().y - FIGHTBTN_SIZE_Y / 2,
		GetPosition().x + FIGHTBTN_SIZE_X / 2, GetPosition().y + FIGHTBTN_SIZE_Y / 2 });
	m_idleImg = new ImageComponent(this, 2);
	m_idleImg->SetImage(L"Image/InterFace/FightButton_Idle.png");
	m_idleImg->SetRect(GetRect());
	m_idleImg->SetIsCam(false);

	m_hoverImg = new ImageComponent(this, 2);
	m_hoverImg->SetImage(L"Image/InterFace/FightButton_Hover.png");
	m_hoverImg->SetRect(GetRect());
	m_hoverImg->SetIsCam(false);

	m_clickImg = new ImageComponent(this, 2);
	m_clickImg->SetImage(L"Image/InterFace/FightButton_Click.png");
	m_clickImg->SetRect(GetRect());
	m_clickImg->SetIsCam(false);

	m_buttonComp = new ButtonComponent(this, 2, this, &FightButton::BattleStart);
	m_buttonComp->SetCollisionRect(GetRect());

	GameObject::Init();
}

void FightButton::Update()
{
	if(GameManager::GetInstance()->GetGameState() == GameState::Stanby)
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

void FightButton::BattleStart()
{
	m_idleImg->SetImage(L"Image/InterFace/FightButton_Disable.png");

	m_buttonComp->SetButtonState(eButtonState::Idle);

	GameManager::GetInstance()->BattleStart();
}

