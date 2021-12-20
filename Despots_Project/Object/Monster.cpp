#include "Monster.h"
#include "Component/ImageComponent.h"
#include "Component/AnimatorComponent.h"
#include "Component/ColiderComponent.h"
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

	m_colider = new ColiderComponent(this, 2, GetRect(), ColTypes::Monster, L"Monster");





	m_state = MonsterState::Burrow;
	m_type = MonsterType::Dalek;

	m_renderRect = GetRect();
	GameObject::Init();
}

void Monster::Update()
{
	GameObject::Update();
	SetDataToType();
	StateUpdate();

	switch (m_dir)
	{
	case MonsterDir::Right:
		// ¿À¸¥ÂÊ º½
		m_idleAni->SetHorizontalReverse(false);
		break;
	case MonsterDir::Left:
		// ¿ÞÂÊ º½
		m_idleAni->SetHorizontalReverse(true);
		break;
	}
	m_burrowImg->SetRect(m_renderRect);
	m_idleAni->SetRect(m_renderRect);

	m_colider->SetRect(GetRect());
}

void Monster::OnColision(ColTypes tag)
{
}

void Monster::Render()
{
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
