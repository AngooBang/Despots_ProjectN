#include "Character.h"
#include "stdafx.h"
#include "Component/AnimatorComponent.h"
#include "Component/ImageComponent.h"
#include "Component/Character/CharacterMovement.h"
#include "Component/Character/CharacterAttack.h"
#include "Component/Monster/MonsterAttack.h"
#include "Util/Timer.h"
#include "Manager/GameManager.h"
#include "Manager/CharacterManager.h"
#include "Object/Monster.h"
#include "Object/HpBar.h"

Character::Character(Scene* scene, Layer* layer, const std::wstring& tag, POINT pos)
	:GameObject(scene, layer, tag)
{
	SetPosition(pos);
}

void Character::Init()
{
	SetRect({ GetPosition().x - 22, GetPosition().y - 40,
			GetPosition().x + 22, GetPosition().y + 22 });
	m_flyDestY = GetPosition().y;
	m_hp = NORMAL_HP;

	m_flyAni = new AnimatorComponent(this, 2);
	m_flyAni->SetImage(L"Image/Character/Normal/Normal_Fly.png");
	m_flyAni->SetFrame(14, 1);
	m_flyAni->SetIsLoop(false);
	m_flyAni->SetMotionSpeed(0.09f);
	m_flyAni->SetScale(2.0f);
	m_flyAni->SetIsVisible(false);

	m_idleAni = new AnimatorComponent(this, 2);
	m_idleAni->SetImage(L"Image/Character/Normal/Normal_Idle.png");
	m_idleAni->SetFrame(6, 1);
	m_idleAni->SetIsLoop(true);
	m_idleAni->SetScale(1.4f);


	m_runAni = new AnimatorComponent(this, 2);
	m_runAni->SetImage(L"Image/Character/Normal/Normal_Run.png");
	m_runAni->SetFrame(8, 1);
	m_runAni->SetIsLoop(true);
	m_runAni->SetMotionSpeed(0.05f);
	m_runAni->SetScale(1.4f);

	m_attackAni = new AnimatorComponent(this, 2);
	m_attackAni->SetImage(L"Image/Character/Normal/Normal_Attack.png");
	m_attackAni->SetFrame(4, 1);
	m_attackAni->SetIsLoop(false);
	m_attackAni->SetMotionSpeed(0.1f);
	m_attackAni->SetScale(1.4f);


	m_selectImg = new ImageComponent(this, 2);
	m_selectImg->SetImage(L"Image/Character/Selected.png");
	m_selectImg->SetIsVisible(false);

	m_hpBar = new HpBar(GetScene(), GetLayer(), L"CHpBar");
	m_hpBar->SetMaxHp(m_hp);
	m_hpBar->SetOwner(this);
	m_hpBar->Init();
	m_hpBar->SetFillImg(L"Image/Character/HpBar_Ally.png");

	m_colider = new ColiderComponent(this, 2, GetRect(), ColTypes::Character, L"Character");
	m_atkRangeCol = new ColiderComponent(this, 1, GetRect(), ColTypes::CAtkRange, L"CAtkRange");
	m_atkCol = new ColiderComponent(this, 1, {}, ColTypes::CAtk, L"CAtk");

	
	m_moveComp = new CharacterMovement(this, 2);
	m_atkComp = new CharacterAttack(this, 1);



	
	// 생성해준뒤 넣어줘야함 이런건 전부 (컴포넌트가 컴포넌트를 가지는(?))
	m_atkComp->SetIdleAni(m_idleAni);
	m_atkComp->SetAtkAni(m_attackAni);
	m_atkComp->SetAtkCol(m_atkCol);
	m_atkComp->SetAttackRange(NORMAL_ATK_RANGE);
	m_atkComp->SetAttackDamage(NORMAL_ATK_DMG);
	m_atkComp->SetAttackSpeed(NORMAL_ATK_SPEED);

	m_atkCol->SetIsAlive(false);
	m_atkCol->SetCAtkComp(m_atkComp);

	m_type = CharacterType::Normal;
	m_state = CharacterState::Idle;

	m_renderRect = GetRect();

	GameObject::Init();

	m_deathAni = new AnimatorComponent(this, 3);
	m_deathAni->SetImage(L"Image/Character/Normal/Normal_Dead.png");
	m_deathAni->SetFrame(10, 1);
	m_deathAni->SetIsLoop(false);
	m_deathAni->SetMotionSpeed(0.06f);
	m_deathAni->SetScale(1.4f);

	m_atkCol->SetImgVisible(false);
}

void Character::Update()
{
	if (!mb_isAlive)
	{
		m_colider->SetIsAlive(false);
		return;
	}

	mb_rangeInMon = false;
	if (m_hp < 0)
		m_hp = 0;
	m_hpBar->SetNowHp(m_hp);
	GameObject::Update();
	SetDataToType();
	if (m_hp <= 0)
	{
		m_state = CharacterState::Dead;
	}
	StateUpdate();
	if (m_deathAni->GetEndAni() && m_state == CharacterState::Dead)
	{
		mb_isAlive = false;
	}

	// 마우스로 선택시 선택프레임출력
	if (mb_isSelected)
		m_selectImg->SetIsVisible(true);
	else  
		m_selectImg->SetIsVisible(false);
	// Fly상태일때 애니메이션이 끝났다면 Idle로
	if (m_flyAni->GetEndAni() && m_state == CharacterState::Fly)
	{
		m_state = CharacterState::Idle;
	}

	switch (m_dir)
	{
	case CharacterDir::Right:
		// 오른쪽 봄
		m_flyAni->SetHorizontalReverse(false);
		m_idleAni->SetHorizontalReverse(false);
		m_runAni->SetHorizontalReverse(false);
		m_attackAni->SetHorizontalReverse(false);
		m_deathAni->SetHorizontalReverse(false);
		break;
	case CharacterDir::Left:
		// 왼쪽 봄
		m_flyAni->SetHorizontalReverse(true);
		m_idleAni->SetHorizontalReverse(true);
		m_runAni->SetHorizontalReverse(true);
		m_attackAni->SetHorizontalReverse(true);
		m_deathAni->SetHorizontalReverse(true);
		break;
	}

	RECT selectRc = { m_renderPos.x - 17, m_renderPos.y, m_renderPos.x + 17, m_renderPos.y + 12 };
	m_selectImg->SetRect(selectRc);

	m_flyAni->SetRect(m_renderRect);
	m_idleAni->SetRect(m_renderRect);
	m_runAni->SetRect(m_renderRect);
	if (m_type == CharacterType::GutSword)
	{
		m_attackAni->SetRect({ m_renderRect.left - 10, m_renderRect.top , m_renderRect.right + 20, m_renderRect.bottom +10 });
	}
	else
	{
		m_attackAni->SetRect(m_renderRect);
	}
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

}

void Character::OnColision(ColTypes tag)
{
	switch (tag)
	{
	case ColTypes::MouseClickUp:
		if (GameManager::GetInstance()->GetCharType() != CharacterType::None)
		{
			m_type = GameManager::GetInstance()->GetCharType();
			mb_isClassChanged = true;
			GameManager::GetInstance()->SetCharType(CharacterType::None);
		}
		break;
	default:
		break;
	}
}

void Character::OnColision(ColiderComponent* col1, ColiderComponent* col2)
{
	switch (col1->GetType())
	{
	case ColTypes::CAtkRange:
		// 사거리 콜라이더에 들어오지 않았을때 false로 해주는 작업도 필요함.
		if (col2->GetType() == ColTypes::Monster && col2->GetIsAlive())
		{
			mb_rangeInMon = true;
			// 길찾기가 완료가 되서 자리를 잡았을 때
			if(m_moveComp->GetIsMove() == false)
				m_state = CharacterState::Attack;

			if (GetRect().left <= col2->GetRect().left)
				m_dir = CharacterDir::Right;
			else
				m_dir = CharacterDir::Left;
		}
		break;
	}
	switch (col2->GetType())
	{
	case ColTypes::MAtk:
		if (col1->GetType() == ColTypes::Character)
		{
			m_hp -= col2->GetMAtkComp()->GetAtkDamage();
			col2->SetIsAlive(false);
		}
		break;
	}

}

void Character::Render()
{
	if (!mb_isAlive) return;
	if (!mb_isVisible) return;
	//ID2D1SolidColorBrush* brush;
	//ImageManagerD2::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkGray), &brush);
	//D2D1_RECT_F rect = { (FLOAT)GetRect().left, (FLOAT)GetRect().top, (FLOAT)GetRect().right, (FLOAT)GetRect().bottom };
	//ImageManagerD2::GetInstance()->GetRenderTarget()->DrawRectangle(rect, brush);	
	GameObject::Render();
}

void Character::FlySavePos()
{
	m_flyDestY = GetPosition().y;
}

void Character::StateUpdate()
{
	if (m_state == CharacterState::End)
	{
		mb_isVisible = false;
		m_hpBar->SetIsVisible(false);
	}
	else
	{
		mb_isVisible = true;
		m_hpBar->SetIsVisible(true);
	}
	switch (m_state)
	{
	case CharacterState::Fly:
		if (m_flyAni->GetIsVisible() == false)
		{
			m_flyAni->SetCurrFrame(0);
			m_flyAni->SetEndAni(false);
			FlySavePos();
			SetPosition({ GetPosition().x, 0 });
		}
		if (GetPosition().y < m_flyDestY)
		{
			SetPosition({ GetPosition().x, (LONG)(GetPosition().y + 1500.0f * Timer::GetDeltaTime()) });
		}
		else
		{
			SetPosition(GetPosition().x, m_flyDestY);
		}
		switch(m_type)
		{
		case CharacterType::GutSword:
			m_renderRect = { m_renderRect.left + 20, m_renderRect.top, m_renderRect.right + 20, m_renderRect.bottom };
			break;
		case CharacterType::Ring:
			m_renderRect = { m_renderRect.left, m_renderRect.top + 10, m_renderRect.right, m_renderRect.bottom +10 };
			break;
		case CharacterType::Crossbow:
			m_renderRect = { m_renderRect.left-10, m_renderRect.top, m_renderRect.right - 10, m_renderRect.bottom  };
			break;
		}
		m_flyAni->SetIsVisible(true);
		m_idleAni->SetIsVisible(false);
		m_runAni->SetIsVisible(false);
		m_attackAni->SetIsVisible(false);
		m_deathAni->SetIsVisible(false);
		break;


	case CharacterState::Idle:
		m_flyAni->SetIsVisible(false);
		m_idleAni->SetIsVisible(true);
		m_runAni->SetIsVisible(false);
		m_attackAni->SetIsVisible(false);
		m_deathAni->SetIsVisible(false);
		break;

	case CharacterState::Run:
		m_flyAni->SetIsVisible(false);
		m_idleAni->SetIsVisible(false);
		m_runAni->SetIsVisible(true);
		m_attackAni->SetIsVisible(false);
		m_deathAni->SetIsVisible(false);
		break;

	case CharacterState::Attack:
		m_flyAni->SetIsVisible(false);
		m_runAni->SetIsVisible(false);
		m_deathAni->SetIsVisible(false);
		break;

	case CharacterState::Dead:
		if (m_deathAni->GetIsVisible() == false)
		{
			m_deathAni->SetCurrFrame(0);
			m_deathAni->SetEndAni(false);
		}
		m_idleAni->SetIsVisible(false);
		m_runAni->SetIsVisible(false);
		m_attackAni->SetIsVisible(false);
		m_deathAni->SetIsVisible(true);
		break;

	default:
		break;
	}
}

void Character::SetDataToType()
{
	m_renderPos = { GetPosition().x + CameraManager::GetInstance()->GetCameraPos().x,
				GetPosition().y + CameraManager::GetInstance()->GetCameraPos().y };
	switch (m_type)
	{
	case CharacterType::Normal:

		m_renderRect = { m_renderPos.x - 22, m_renderPos.y - 40,
			m_renderPos.x + 22, m_renderPos.y + 22 };
		SetRect({ GetPosition().x - 22, GetPosition().y - 40,
			GetPosition().x + 22, GetPosition().y + 22 });

		if (mb_isClassChanged)
		{
			m_idleAni->SetImage(L"Image/Character/Normal/Normal_Idle.png");
			m_idleAni->SetFrame(6, 1);
			m_runAni->SetImage(L"Image/Character/Normal/Normal_Run.png");
			m_runAni->SetFrame(8, 1);
			m_attackAni->SetImage(L"Image/Character/Normal/Normal_Attack.png");
			m_attackAni->SetFrame(4, 1);

			m_hp = NORMAL_HP;
			m_hpBar->SetMaxHp(m_hp);
			mb_isClassChanged = false;
		}
		break;
	case CharacterType::GutSword:
		m_renderRect = { m_renderPos.x - 50, m_renderPos.y - 40,
			m_renderPos.x + 30, m_renderPos.y + 22 };

		SetRect({ GetPosition().x - 22, GetPosition().y - 40,
			GetPosition().x + 22, GetPosition().y + 22 });

		m_atkComp->SetAttackRange(GUTS_ATK_RANGE);
		m_atkComp->SetAttackDamage(GUTS_ATK_DMG);
		m_atkComp->SetAttackSpeed(GUTS_ATK_SPEED);

		if (mb_isClassChanged)
		{
			m_flyAni->SetImage(L"Image/Character/Swordman/GutsSword_Fly.png");
			m_flyAni->SetFrame(14, 1);
			m_idleAni->SetImage(L"Image/Character/Swordman/GutsSword_Idle.png");
			m_idleAni->SetFrame(6, 1);
			m_runAni->SetImage(L"Image/Character/Swordman/GutsSword_Run.png");
			m_runAni->SetFrame(12, 1);
			m_attackAni->SetImage(L"Image/Character/Swordman/GutsSword_Attack.png");
			m_attackAni->SetFrame(10, 1);
			m_attackAni->SetMotionSpeed(0.06f);
			m_attackAni->SetScale(2.5f);

			m_hp = GUTS_HP;
			m_hpBar->SetMaxHp(m_hp);
			mb_isClassChanged = false;
		}
		break;
	case CharacterType::Shield:
		m_renderRect = { m_renderPos.x - 28, m_renderPos.y - 45,
			m_renderPos.x + 28, m_renderPos.y + 22 };

		SetRect({ GetPosition().x - 22, GetPosition().y - 40,
			GetPosition().x + 22, GetPosition().y + 22 });

		m_atkComp->SetAttackRange(SHIELD_ATK_RANGE);
		m_atkComp->SetAttackDamage(SHIELD_ATK_DMG);
		m_atkComp->SetAttackSpeed(SHIELD_ATK_SPEED);

		if (mb_isClassChanged)
		{
			m_flyAni->SetImage(L"Image/Character/Tanker/Shield_Fly.png");
			m_flyAni->SetFrame(14, 1);
			m_idleAni->SetImage(L"Image/Character/Tanker/Shield_Idle.png");
			m_idleAni->SetFrame(6, 1);
			m_runAni->SetImage(L"Image/Character/Tanker/Shield_Run.png");
			m_runAni->SetFrame(6, 1);
			m_attackAni->SetImage(L"Image/Character/Tanker/Shield_Attack.png");
			m_attackAni->SetFrame(3, 1);

			m_hp = SHIELD_HP;
			m_hpBar->SetMaxHp(m_hp);
			mb_isClassChanged = false;
		}
		break;
	case CharacterType::Crossbow:
		m_renderRect = { m_renderPos.x - 22, m_renderPos.y - 40,
			m_renderPos.x + 40, m_renderPos.y + 22 };

		SetRect({ GetPosition().x - 22, GetPosition().y - 40,
			GetPosition().x + 22, GetPosition().y + 22 });

		m_atkComp->SetIsCloseRange(false);
		m_atkComp->SetBulletSize(20);
		m_atkComp->SetBulletSpeed(800.0f);

		m_atkComp->SetAttackRange(CROSSBOW_ATK_RANGE);
		m_atkComp->SetAttackDamage(CROSSBOW_ATK_DMG);
		m_atkComp->SetAttackSpeed(CROSSBOW_ATK_SPEED);

		if (mb_isClassChanged)
		{
			m_flyAni->SetImage(L"Image/Character/Shooter/Crossbow_Fly.png");
			m_flyAni->SetFrame(14, 1);
			m_idleAni->SetImage(L"Image/Character/Shooter/Crossbow_Idle.png");
			m_idleAni->SetFrame(6, 1);
			m_runAni->SetImage(L"Image/Character/Shooter/Crossbow_Run.png");
			m_runAni->SetFrame(6, 1);
			m_attackAni->SetImage(L"Image/Character/Shooter/Crossbow_Attack.png");
			m_attackAni->SetFrame(3, 1);
			m_atkCol->SetImage(L"Image/Character/Shooter/Crossbow_Bullet.png");
			m_atkCol->SetImgVisible(true);

			m_hp = CROSSBOW_HP;
			m_hpBar->SetMaxHp(m_hp);
			mb_isClassChanged = false;
		}
		break;
	case CharacterType::Ring:
		m_renderRect = { m_renderPos.x - 30, m_renderPos.y - 60,
			m_renderPos.x + 30, m_renderPos.y + 22 };

		m_atkComp->SetIsCloseRange(false);
		m_atkComp->SetBulletSize(30);
		m_atkComp->SetBulletSpeed(400.0f);

		m_atkComp->SetAttackRange(RING_ATK_RANGE);
		m_atkComp->SetAttackDamage(RING_ATK_DMG);
		m_atkComp->SetAttackSpeed(RING_ATK_SPEED);

		SetRect({ GetPosition().x - 22, GetPosition().y - 40,
			GetPosition().x + 22, GetPosition().y + 22 });

		if (mb_isClassChanged)
		{
			m_flyAni->SetImage(L"Image/Character/Mage/Ring_Fly.png");
			m_flyAni->SetFrame(14, 1);
			m_idleAni->SetImage(L"Image/Character/Mage/Ring_Idle.png");
			m_idleAni->SetFrame(6, 1);
			m_idleAni->SetMotionSpeed(0.08f);
			m_runAni->SetImage(L"Image/Character/Mage/Ring_Run.png");
			m_runAni->SetFrame(6, 1);
			m_attackAni->SetImage(L"Image/Character/Mage/Ring_Attack.png");
			m_attackAni->SetFrame(4, 1);
			m_atkCol->SetImage(L"Image/Character/Mage/Ring_Bullet.png");
			m_atkCol->SetImgVisible(true);

			m_hp = RING_HP;
			m_hpBar->SetMaxHp(m_hp);
			mb_isClassChanged = false;
		}
		break;
	}
}



void Character::SetState(CharacterState state)
{
	m_state = state;
}

void Character::SetType(CharacterType type)
{
	m_type = type;
}

void Character::SetIsSelected(bool isSelected)
{
	mb_isSelected = isSelected;
}

void Character::SetTilePos(POINT pos)
{
	m_tilePos = pos;
}

void Character::SetStanbyPos(POINT pos)
{
	m_stanbyPos = pos;
}

POINT Character::GetTilePos()
{
	return m_tilePos;
}

POINT Character::GetStanbyPos()
{
	return m_stanbyPos;
}


bool Character::GetIsSelected()
{
	return mb_isSelected;
}

bool Character::GetIsRangeInMon()
{
	return mb_rangeInMon;
}

bool Character::GetIsAlive()
{
	return mb_isAlive;
}

bool Character::GetIsMove()
{
	if (m_target == nullptr) return false;
	return m_moveComp->GetIsMove();
}

CharacterState Character::GetState()
{
	return m_state;
}

CharacterDir Character::GetDir()
{
	return m_dir;
}

CharacterType Character::GetCType()
{
	return m_type;
}

Monster* Character::GetTarget()
{
	return m_target;
}

POINT Character::GetRenderRect()
{
	return m_renderPos;
}

void Character::SetPath(deque<POINT> path)
{
	m_moveComp->SetPath(path);
}

void Character::SetDir(CharacterDir dir)
{
	m_dir = dir;
}

void Character::SetTarget(Monster* target)
{
	m_target = target;
}

void Character::SetIsClassChanged(bool isClassChanged)
{
	mb_isClassChanged = isClassChanged;
}
