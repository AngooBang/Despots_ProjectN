#include "Monster.h"
#include "stdafx.h"
#include "Component/ImageComponent.h"
#include "Component/AnimatorComponent.h"
#include "Component/ColiderComponent.h"
#include "Component/Character/CharacterAttack.h"
#include "Component/Monster/MonsterMovement.h"
#include "Component/Monster/MonsterAttack.h"
#include "Manager/CameraManager.h"
#include "Manager/GameManager.h"
#include "Object/HpBar.h"

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
	m_idleAni->SetIsLoop(true);
	m_idleAni->SetScale(1.5f);

	m_runAni = new AnimatorComponent(this, 2);
	m_runAni->SetImage(L"Image/Monster/Dalek_Run.png");
	m_runAni->SetFrame(6, 1);
	m_runAni->SetMotionSpeed(0.05f);
	m_runAni->SetIsLoop(true);
	m_runAni->SetScale(1.5f);

	m_attackAni = new AnimatorComponent(this, 2);
	m_attackAni->SetImage(L"Image/Monster/Dalek_Attack.png");
	m_attackAni->SetFrame(4, 1);
	m_attackAni->SetIsLoop(false);
	m_attackAni->SetMotionSpeed(0.1f);
	m_attackAni->SetScale(1.5f);

	m_deathAni = new AnimatorComponent(this, 2);
	m_deathAni->SetImage(L"Image/Monster/Dalek_Death.png");
	m_deathAni->SetFrame(8, 1);
	m_deathAni->SetRect(GetRect());
	m_deathAni->SetIsVisible(false);
	m_deathAni->SetIsLoop(false);
	m_deathAni->SetScale(1.5f);

	m_hpBar = new HpBar(GetScene(), GetLayer(), L"CHpBar");
	m_hpBar->SetOwner(this);
	m_hpBar->Init();
	m_hpBar->SetFillImg(L"Image/Character/HpBar_Enemy.png");

	m_colider = new ColiderComponent(this, 2, GetRect(), ColTypes::Monster, L"Monster");
	m_atkRangeCol = new ColiderComponent(this, 1, GetRect(), ColTypes::MAtkRange, L"MAtkRange");
	m_atkCol = new ColiderComponent(this, 1, {}, ColTypes::MAtk, L"MAtk");

	m_moveComp = new MonsterMovement(this, 2);
	m_atkComp = new MonsterAttack(this, 1);

	// 생성해준뒤 넣어줘야함 이런건 전부 (컴포넌트가 컴포넌트를 가지는(?))
	m_atkComp->SetIdleAni(m_idleAni);
	m_atkComp->SetAtkAni(m_attackAni);
	m_atkComp->SetAtkCol(m_atkCol);
	m_atkComp->SetAttackRange(DALEK_ATK_RANGE);
	m_atkComp->SetAttackDamage(DALEK_ATK_DMG);
	m_atkComp->SetAttackSpeed(DALEK_ATK_SPEED);

	m_atkCol->SetIsAlive(false);
	m_atkCol->SetMAtkComp(m_atkComp);

	m_state = MonsterState::Burrow;

	switch (m_type)
	{
	case MonsterType::Dalek:
		m_hp = DALEK_HP;
		break;
	case MonsterType::Necro:
		m_hp = NECRO_HP;
		break;
	case MonsterType::Octopus:
		m_hp = OCTO_HP;
		break;
	case MonsterType::Boss:
		m_hp = BOSS_HP;
		break;
	}
	m_hpBar->SetMaxHp(m_hp);

	m_renderRect = GetRect();
	GameObject::Init();
	m_atkCol->SetImgVisible(false);
}

void Monster::Update()
{
	if (!mb_isAlive)
	{
		m_colider->SetIsAlive(false);
		return;
	}
	mb_rangeInChar = false;
	if (m_hp < 0)
		m_hp = 0;
	m_hpBar->SetNowHp(m_hp);
	GameObject::Update();
	SetDataToType();
	if (m_hp <= 0)
	{
		m_state = MonsterState::Dead;
	}
	StateUpdate();
	if (m_deathAni->GetEndAni() && m_state == MonsterState::Dead)
	{
		mb_isAlive = false;
	}
	if (m_type == MonsterType::Boss)
	{
		switch (m_dir)
		{
		case MonsterDir::Right:
			// 오른쪽 봄
			m_idleAni->SetHorizontalReverse(true);
			m_runAni->SetHorizontalReverse(true);
			m_attackAni->SetHorizontalReverse(true);
			m_deathAni->SetHorizontalReverse(true);
			break;
		case MonsterDir::Left:
			// 왼쪽 봄
			m_idleAni->SetHorizontalReverse(false);
			m_runAni->SetHorizontalReverse(false);
			m_attackAni->SetHorizontalReverse(false);
			m_deathAni->SetHorizontalReverse(false);
			break;
		}
	}
	else
	{
		switch (m_dir)
		{
		case MonsterDir::Right:
			// 오른쪽 봄
			m_idleAni->SetHorizontalReverse(false);
			m_runAni->SetHorizontalReverse(false);
			m_attackAni->SetHorizontalReverse(false);
			m_deathAni->SetHorizontalReverse(false);
			break;
		case MonsterDir::Left:
			// 왼쪽 봄
			m_idleAni->SetHorizontalReverse(true);
			m_runAni->SetHorizontalReverse(true);
			m_attackAni->SetHorizontalReverse(true);
			m_deathAni->SetHorizontalReverse(true);
			break;
		}
	}
	m_burrowImg->SetRect(m_renderRect);
	m_idleAni->SetRect(m_renderRect);
	m_runAni->SetRect(m_renderRect);
	m_attackAni->SetRect(m_renderRect);
	m_deathAni->SetRect(m_renderRect);

	m_colider->SetRect(GetRect());
	m_atkRangeCol->SetRect(GetRect(m_atkComp->GetAtkRange()));
	if (GameManager::GetInstance()->GetGameState() == GameState::Battle)
	{
		m_atkRangeCol->SetIsAlive(true);
	}
	else
	{
		m_atkRangeCol->SetIsAlive(false);
	}

	if (m_atkCol->GetIsAlive() == false)
	{
		m_atkCol->SetImgVisible(false);
	}


}

void Monster::OnColision(ColiderComponent* col1, ColiderComponent* col2)
{
	switch (col1->GetType())
	{
	case ColTypes::MAtkRange:
		// 사거리 콜라이더에 들어오지 않았을때 false로 해주는 작업도 필요함.
		if (col2->GetType() == ColTypes::Character)
		{
			mb_rangeInChar = true;
			// 길찾기가 완료가 되서 자리를 잡았을 때

			if (m_moveComp->GetIsMove() == false)
				m_state = MonsterState::Attack;
			if (GetRect().left <= col2->GetRect().left)
				m_dir = MonsterDir::Right;
			else
				m_dir = MonsterDir::Left;
		}
		break;
	}
	switch (col2->GetType())
	{
	case ColTypes::CAtk:
		if (col1->GetType() == ColTypes::Monster)
		{
			m_hp -= col2->GetCAtkComp()->GetAtkDamage();
			col2->SetIsAlive(false);
		}
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
		m_idleAni->SetIsVisible(false);
		m_runAni->SetIsVisible(false);
		m_attackAni->SetIsVisible(false);
		m_deathAni->SetIsVisible(false);
		break;
	case MonsterState::Idle:
		m_burrowImg->SetIsVisible(false);
		m_idleAni->SetIsVisible(true);
		m_runAni->SetIsVisible(false);
		m_attackAni->SetIsVisible(false);
		m_deathAni->SetIsVisible(false);
		break;
	case MonsterState::Run:
		m_burrowImg->SetIsVisible(false);
		m_idleAni->SetIsVisible(false);
		m_runAni->SetIsVisible(true);
		m_attackAni->SetIsVisible(false);
		m_deathAni->SetIsVisible(false);
		break;
	case MonsterState::Attack:
		m_burrowImg->SetIsVisible(false);
		m_runAni->SetIsVisible(false);
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
		m_runAni->SetIsVisible(false);
		m_attackAni->SetIsVisible(false);
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
		m_renderRect = { renderPos.x - 22, renderPos.y - 30,
		renderPos.x + 22, renderPos.y + 30 };
		SetRect({ GetPosition().x - 22, GetPosition().y - 40,
		GetPosition().x + 22, GetPosition().y + 22 });

		m_atkComp->SetIsCloseRange(false);
		m_atkComp->SetBulletSize(20);
		m_atkComp->SetBulletSpeed(500.0f);

		m_atkComp->SetAttackRange(DALEK_ATK_RANGE);
		m_atkComp->SetAttackDamage(DALEK_ATK_DMG);
		m_atkComp->SetAttackSpeed(DALEK_ATK_SPEED);

		m_idleAni->SetImage(L"Image/Monster/Dalek_Idle.png");
		m_idleAni->SetFrame(6, 1);
		m_idleAni->SetScale(7.0f);
		m_runAni->SetImage(L"Image/Monster/Dalek_Run.png");
		m_runAni->SetFrame(6, 1);
		m_runAni->SetScale(7.0f);
		m_attackAni->SetImage(L"Image/Monster/Dalek_Attack.png");
		m_attackAni->SetFrame(9, 1);
		m_attackAni->SetScale(7.0f);
		m_deathAni->SetImage(L"Image/Monster/Dalek_Death.png");
		m_deathAni->SetFrame(8, 1);
		m_deathAni->SetScale(7.0f);
		m_atkCol->SetImage(L"Image/Monster/Dalek_Bullet.png");
		m_atkCol->SetImgVisible(true);

		m_hpBar->SetDistance(15);
		break;
	case MonsterType::Necro:
		m_renderRect = { renderPos.x - 30, renderPos.y - 30,
		renderPos.x + 30, renderPos.y + 40 };
		SetRect({ GetPosition().x - 22, GetPosition().y - 40,
		GetPosition().x + 22, GetPosition().y + 22 });

		m_atkComp->SetIsCloseRange(true);

		m_atkComp->SetAttackRange(NECRO_ATK_RANGE);
		m_atkComp->SetAttackDamage(NECRO_ATK_DMG);
		m_atkComp->SetAttackSpeed(NECRO_ATK_SPEED);

		m_idleAni->SetImage(L"Image/Monster/Necro/Necro_Idle.png");
		m_idleAni->SetFrame(6, 1);
		m_idleAni->SetScale(4.0f);
		m_runAni->SetImage(L"Image/Monster/Necro/Necro_Run.png");
		m_runAni->SetFrame(15, 1);
		m_runAni->SetScale(4.0f);
		m_attackAni->SetImage(L"Image/Monster/Necro/Necro_Attack.png");
		m_attackAni->SetFrame(16, 1);
		m_attackAni->SetScale(4.0f);
		m_deathAni->SetImage(L"Image/Monster/Necro/Necro_Death.png");
		m_deathAni->SetFrame(14, 1);
		m_deathAni->SetScale(4.0f);

		m_hpBar->SetDistance(25);
		m_hpBar->SetWidth(30);
		m_hpBar->SetHeight(6);
		break;
	case MonsterType::Octopus:
		m_renderRect = { renderPos.x - 30, renderPos.y - 30,
		renderPos.x + 30, renderPos.y + 40 };
		SetRect({ GetPosition().x - 22, GetPosition().y - 40,
		GetPosition().x + 22, GetPosition().y + 22 });

		m_atkComp->SetIsCloseRange(true);

		m_atkComp->SetAttackRange(OCTO_ATK_RANGE);
		m_atkComp->SetAttackDamage(OCTO_ATK_DMG);
		m_atkComp->SetAttackSpeed(OCTO_ATK_SPEED);

		m_idleAni->SetImage(L"Image/Monster/Octopus/Octopus_Idle.png");
		m_idleAni->SetFrame(10, 1);
		m_idleAni->SetScale(4.0f);
		m_runAni->SetImage(L"Image/Monster/Octopus/Octopus_Run.png");
		m_runAni->SetFrame(14, 1);
		m_runAni->SetScale(4.0f);
		m_attackAni->SetImage(L"Image/Monster/Octopus/Octopus_Attack.png");
		m_attackAni->SetFrame(12, 1);
		m_attackAni->SetScale(4.0f);
		m_deathAni->SetImage(L"Image/Monster/Octopus/Octopus_Death.png");
		m_deathAni->SetFrame(18, 1);
		m_deathAni->SetScale(4.0f);

		m_hpBar->SetDistance(25);
		m_hpBar->SetWidth(30);
		m_hpBar->SetHeight(6);
		break;
	case MonsterType::Boss:
		m_renderRect = { renderPos.x - 30, renderPos.y - 30,
		renderPos.x + 30, renderPos.y + 40 };
		SetRect({ GetPosition().x - 60, GetPosition().y - 80,
		GetPosition().x + 60, GetPosition().y + 60 });

		m_atkComp->SetIsCloseRange(true);

		m_atkComp->SetAttackRange(BOSS_ATK_RANGE);
		m_atkComp->SetAttackDamage(BOSS_ATK_DMG);
		m_atkComp->SetAttackSpeed(BOSS_ATK_SPEED);


		m_idleAni->SetImage(L"Image/Monster/Boss/Boss_Idle.png");
		m_idleAni->SetFrame(10, 1);
		m_idleAni->SetScale(3.0f);
		m_runAni->SetImage(L"Image/Monster/Boss/Boss_Run.png");
		m_runAni->SetFrame(11, 1);
		m_runAni->SetScale(3.0f);
		m_attackAni->SetImage(L"Image/Monster/Boss/Boss_Attack.png");
		m_attackAni->SetFrame(11, 1);
		m_attackAni->SetScale(4.5f);
		m_deathAni->SetImage(L"Image/Monster/Boss/Boss_Death.png");
		m_deathAni->SetFrame(10, 1);
		m_deathAni->SetScale(5.0f);
		m_deathAni->SetMotionSpeed(0.09f);

		m_hpBar->SetDistance(20);
		m_hpBar->SetWidth(100);
		m_hpBar->SetHeight(10);
		break;
	}
}

POINT Monster::GetTilePos()
{
	return m_tilePos;
}

MonsterType Monster::GetMType()
{
	return m_type;
}

MonsterState Monster::GetState()
{
	return m_state;
}

MonsterDir Monster::GetDir()
{
	return m_dir;
}

Character* Monster::GetTarget()
{
	return m_target;
}

bool Monster::GetIsSelected()
{
	return mb_isSelected;
}

bool Monster::GetIsAlive()
{
	return mb_isAlive;
}

bool Monster::GetRangeInChar()
{
	return mb_rangeInChar;
}

bool Monster::GetIsMove()
{
	if (this == nullptr) return false;
	return m_moveComp->GetIsMove();
}

void Monster::SetType(MonsterType type)
{
	m_type = type;
}

void Monster::SetTarget(Character* target)
{
	m_target = target;
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

void Monster::SetPath(deque<POINT> path)
{
	m_moveComp->SetPath(path);
}

void Monster::SetDir(MonsterDir dir)
{
	m_dir = dir;
}
