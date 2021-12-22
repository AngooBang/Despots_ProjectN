#include "Monster.h"
#include "stdafx.h"
#include "Component/ImageComponent.h"
#include "Component/AnimatorComponent.h"
#include "Component/ColiderComponent.h"
#include "Component/Character/CharacterAttack.h"
#include "Manager/CameraManager.h"

Monster::Monster(Scene* scene, Layer* layer, const std::wstring& tag, POINT pos)
	:GameObject(scene, layer, tag)
{
	SetPosition(pos);
}

void Monster::Init()
{
	SetRect({ GetPosition().x - 22, GetPosition().y - 40,
		GetPosition().x + 22, GetPosition().y + 22 });

	m_burrowImg = new ImageComponent(this, 2);
	m_burrowImg->SetImage(L"Image/Monster/Burrow.png");
	m_burrowImg->SetRect(GetRect());

	m_idleAni = new AnimatorComponent(this, 2);
	m_idleAni->SetImage(L"Image/Monster/Dalek_Idle.png");
	m_idleAni->SetFrame(6, 1);
	m_idleAni->SetRect(GetRect());
	m_idleAni->SetIsVisible(false);
	m_idleAni->SetIsLoop(true);
	m_idleAni->SetScale(1.5f);

	m_deathAni = new AnimatorComponent(this, 2);
	m_deathAni->SetImage(L"Image/Monster/Dalek_Death.png");
	m_deathAni->SetFrame(8, 1);
	m_deathAni->SetRect(GetRect());
	m_deathAni->SetIsVisible(false);
	m_deathAni->SetIsLoop(false);
	m_deathAni->SetScale(1.5f);

	m_colider = new ColiderComponent(this, 2, GetRect(), ColTypes::Monster, L"Monster");





	m_state = MonsterState::Burrow;
	m_type = MonsterType::Dalek;

	m_renderRect = GetRect();
	GameObject::Init();
}

void Monster::Update()
{
	if (!mb_isAlive)
	{
		m_colider->SetIsAlive(false);
		return;
	}
	GameObject::Update();
	SetDataToType();
	StateUpdate();

	if (m_deathAni->GetEndAni() && m_state == MonsterState::Dead)
	{
		mb_isAlive = false;
	}

	if (m_hp <= 0)
	{
		m_state = MonsterState::Dead;
	}



	switch (m_dir)
	{
	case MonsterDir::Right:
		// ¿À¸¥ÂÊ º½
		m_idleAni->SetHorizontalReverse(false);
		m_deathAni->SetHorizontalReverse(false);
		break;
	case MonsterDir::Left:
		// ¿ÞÂÊ º½
		m_idleAni->SetHorizontalReverse(true);
		m_deathAni->SetHorizontalReverse(true);
		break;
	}
	m_burrowImg->SetRect(m_renderRect);
	m_idleAni->SetRect(m_renderRect);
	m_deathAni->SetRect(m_renderRect);

	m_colider->SetRect(GetRect());
}

void Monster::OnColision(ColiderComponent* col1, ColiderComponent* col2)
{
	switch (col2->GetType())
	{
	case ColTypes::CAtk:
		m_hp -= col2->GetCAtkComp()->GetAtkDamage();
		col2->SetIsAlive(false);
		break;
	}
}



void Monster::Render()
{
	if (!mb_isAlive) return;
	GameObject::Render();
}

void Monster::StateUpdate()
{
	switch (m_state)
	{
	case MonsterState::Burrow:
		m_burrowImg->SetIsVisible(true);
		break;
	case MonsterState::Idle:
		m_burrowImg->SetIsVisible(false);
		m_idleAni->SetIsVisible(true);
		m_deathAni->SetIsVisible(false);
		break;
	case MonsterState::Dead:
		if (m_deathAni->GetIsVisible() == false)
		{
			m_deathAni->SetCurrFrame(0);
			m_deathAni->SetEndAni(false);
		}
		m_burrowImg->SetIsVisible(false);
		m_idleAni->SetIsVisible(false);
		m_deathAni->SetIsVisible(true);
		break;
	}
}

void Monster::SetDataToType()
{
	POINT renderPos = { GetPosition().x + CameraManager::GetInstance()->GetCameraPos().x,
			GetPosition().y + CameraManager::GetInstance()->GetCameraPos().y };
	switch (m_type)
	{
	case MonsterType::Dalek:
		m_renderRect = { renderPos.x - 22, renderPos.y - 40,
		renderPos.x + 22, renderPos.y + 22 };
		SetRect({ GetPosition().x - 22, GetPosition().y - 40,
		GetPosition().x + 22, GetPosition().y + 22 });

		m_idleAni->SetImage(L"Image/Monster/Dalek_Idle.png");
		m_idleAni->SetFrame(6, 1);

		m_deathAni->SetImage(L"Image/Monster/Dalek_Death.png");
		m_deathAni->SetFrame(8, 1);
		break;
	}
}

POINT Monster::GetTilePos()
{
	return m_tilePos;
}

bool Monster::GetIsSelected()
{
	return mb_isSelected;
}

bool Monster::GetIsAlive()
{
	return mb_isAlive;
}

void Monster::SetState(MonsterState state)
{
	m_state = state;
}

void Monster::SetIsSelected(bool isSelected)
{
	mb_isSelected = isSelected;
}

void Monster::SetTilePos(POINT pos)
{
	m_tilePos = pos;
}
