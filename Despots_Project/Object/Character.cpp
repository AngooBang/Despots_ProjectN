#include "Character.h"
#include "stdafx.h"
#include "Component/AnimatorComponent.h"
#include "Component/ImageComponent.h"
#include "Component/Character/CharacterMovement.h"
#include "Component/Character/CharacterAttack.h"
#include "Util/Timer.h"
#include "Manager/GameManager.h"

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

	m_flyAni = new AnimatorComponent(this, 2);
	m_flyAni->SetImage(L"Image/Character/Normal/Normal_Fly.png");
	m_flyAni->SetFrame(14, 1);
	m_flyAni->SetIsLoop(false);
	m_flyAni->SetMotionSpeed(90.0f);
	m_flyAni->SetScale(2.0f);

	m_idleAni = new AnimatorComponent(this, 2);
	m_idleAni->SetImage(L"Image/Character/Normal/Normal_Idle.png");
	m_idleAni->SetFrame(6, 1);
	m_idleAni->SetIsLoop(true);
	m_idleAni->SetScale(1.4f);


	m_runAni = new AnimatorComponent(this, 2);
	m_runAni->SetImage(L"Image/Character/Normal/Normal_Run.png");
	m_runAni->SetFrame(8, 1);
	m_runAni->SetIsLoop(true);
	m_runAni->SetMotionSpeed(50.0f);
	m_runAni->SetScale(1.4f);

	m_attackAni = new AnimatorComponent(this, 2);
	m_attackAni->SetImage(L"Image/Character/Normal/Normal_Attack.png");
	m_attackAni->SetFrame(4, 1);
	m_attackAni->SetIsLoop(false);
	m_attackAni->SetMotionSpeed(100.0f);
	m_attackAni->SetScale(1.4f);


	m_selectImg = new ImageComponent(this, 2);
	m_selectImg->SetImage(L"Image/Character/Selected.png");
	m_selectImg->SetIsVisible(false);

	m_colider = new ColiderComponent(this, 1, GetRect(), ColTypes::Character, L"Character");


	m_atkRange = NORMAL_ATK_RANGE;
	m_atkRangeCol = new ColiderComponent(this, 1, GetRect(m_atkRange), ColTypes::CAtkRange, L"CAtkRange");
	
	m_moveComp = new CharacterMovement(this, 1);


	m_atkComp = new CharacterAttack(this, 1);
	m_atkCol = new ColiderComponent(this, 1, {}, ColTypes::CAtk, L"CAtk");
	
	// �������ص� �־������ �̷��� ���� (������Ʈ�� ������Ʈ�� ������(?))
	m_atkComp->SetIdleAni(m_idleAni);
	m_atkComp->SetAtkAni(m_attackAni);
	m_atkComp->SetAtkCol(m_atkCol);

	m_atkCol->SetIsAlive(false);
	m_atkCol->SetCAtkComp(m_atkComp);

	m_type = CharacterType::Normal;
	m_state = CharacterState::Idle;

	m_renderRect = GetRect();

	GameObject::Init();
	
}

void Character::Update()
{
	mb_rangeInMon = false;
	GameObject::Update();

	SetDataToType();
	StateUpdate();



	if (mb_isSelected)
		m_selectImg->SetIsVisible(true);
	else  
		m_selectImg->SetIsVisible(false);

	if (m_flyAni->GetEndAni() && m_state == CharacterState::Fly)
	{
		m_state = CharacterState::Idle;
	}




	switch (m_dir)
	{
	case CharacterDir::Right:
		// ������ ��
		m_flyAni->SetHorizontalReverse(false);
		m_idleAni->SetHorizontalReverse(false);
		m_runAni->SetHorizontalReverse(false);
		m_attackAni->SetHorizontalReverse(false);
		break;
	case CharacterDir::Left:
		// ���� ��
		m_flyAni->SetHorizontalReverse(true);
		m_idleAni->SetHorizontalReverse(true);
		m_runAni->SetHorizontalReverse(true);
		m_attackAni->SetHorizontalReverse(true);
		break;
	}

	RECT selectRc = { m_renderPos.x - 17, m_renderPos.y, m_renderPos.x + 17, m_renderPos.y + 12 };
	m_selectImg->SetRect(selectRc);

	m_flyAni->SetRect(m_renderRect);
	m_idleAni->SetRect(m_renderRect);
	m_runAni->SetRect(m_renderRect);
	m_attackAni->SetRect(m_renderRect);

	m_colider->SetRect(GetRect());
	m_atkRangeCol->SetRect(GetRect(m_atkRange));


}

void Character::OnColision(ColTypes tag)
{
	switch (tag)
	{
	case ColTypes::MouseClickUp:
		if (GameManager::GetInstance()->GetCharType() != CharacterType::None)
		{
			m_type = GameManager::GetInstance()->GetCharType();

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
		// ��Ÿ� �ݶ��̴��� ������ �ʾ����� false�� ���ִ� �۾��� �ʿ���.
		if (col2->GetType() == ColTypes::Monster)
			mb_rangeInMon = true;

		break;

	}

}

void Character::Render()
{
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
		mb_isVisible = false;
	else
		mb_isVisible = true;
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
			SetPosition({ GetPosition().x, (LONG)(GetPosition().y + 1.5f * Timer::GetDeltaTime()) });
		}
		else
		{
			SetPosition(GetPosition().x, m_flyDestY);
		}
		if (m_type == CharacterType::GutSword)
		{
			m_renderRect = { m_renderRect.left + 20, m_renderRect.top, m_renderRect.right + 20, m_renderRect.bottom };
		}
		m_flyAni->SetIsVisible(true);
		m_idleAni->SetIsVisible(false);
		m_runAni->SetIsVisible(false);
		m_attackAni->SetIsVisible(false);
		break;


	case CharacterState::Idle:
		m_flyAni->SetIsVisible(false);
		m_idleAni->SetIsVisible(true);
		m_runAni->SetIsVisible(false);
		m_attackAni->SetIsVisible(false);
		break;

	case CharacterState::Run:
		m_flyAni->SetIsVisible(false);
		m_idleAni->SetIsVisible(false);
		m_runAni->SetIsVisible(true);
		m_attackAni->SetIsVisible(false);
		break;

	case CharacterState::Attack:
		m_flyAni->SetIsVisible(false);
		//m_idleAni->SetIsVisible(false);
		m_runAni->SetIsVisible(false);
		//m_attackAni->SetIsVisible(false);
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

		m_idleAni->SetImage(L"Image/Character/Normal/Normal_Idle.png");
		m_idleAni->SetFrame(6, 1);

		m_runAni->SetImage(L"Image/Character/Normal/Normal_Run.png");
		m_runAni->SetFrame(8, 1);

		m_attackAni->SetImage(L"Image/Character/Normal/Normal_Attack.png");
		m_attackAni->SetFrame(4, 1);
		switch (m_dir)
		{
		case CharacterDir::Left:
			m_atkCol->SetRect({ GetPosition().x - 32, GetPosition().y - 30, GetPosition().x,  GetPosition().y + 30 });
			break;
		case CharacterDir::Right:
			m_atkCol->SetRect({ GetPosition().x, GetPosition().y - 30, GetPosition().x + 32,  GetPosition().y + 30 });
			break;
		default:
			break;
		}
		break;
	case CharacterType::GutSword:
		m_renderRect = { m_renderPos.x - 50, m_renderPos.y - 40,
			m_renderPos.x + 30, m_renderPos.y + 22 };

		SetRect({ GetPosition().x - 22, GetPosition().y - 40,
			GetPosition().x + 22, GetPosition().y + 22 });

		m_flyAni->SetImage(L"Image/Character/Swordman/GutsSword_Fly.png");
		m_flyAni->SetFrame(14, 1);
		m_idleAni->SetImage(L"Image/Character/Swordman/GutsSword_Idle.png");
		m_idleAni->SetFrame(6, 1);

		m_runAni->SetImage(L"Image/Character/Swordman/GutsSword_Run.png");
		m_runAni->SetFrame(12, 1);
		break;
	case CharacterType::Shield:
		m_renderRect = { m_renderPos.x - 28, m_renderPos.y - 45,
			m_renderPos.x + 28, m_renderPos.y + 22 };

		SetRect({ GetPosition().x - 22, GetPosition().y - 40,
			GetPosition().x + 22, GetPosition().y + 22 });
		m_idleAni->SetImage(L"Image/Character/Tanker/Shield_Idle.png");
		m_idleAni->SetFrame(6, 1);

		m_runAni->SetImage(L"Image/Character/Tanker/Shield_Run.png");
		m_runAni->SetFrame(6, 1);
		break;
	case CharacterType::Crossbow:
		m_renderRect = { m_renderPos.x - 22, m_renderPos.y - 40,
			m_renderPos.x + 40, m_renderPos.y + 22 };

		SetRect({ GetPosition().x - 22, GetPosition().y - 40,
			GetPosition().x + 22, GetPosition().y + 22 });
		m_idleAni->SetImage(L"Image/Character/Shooter/Crossbow_Idle.png");
		m_idleAni->SetFrame(6, 1);

		m_runAni->SetImage(L"Image/Character/Shooter/Crossbow_Run.png");
		m_runAni->SetFrame(6, 1);
		break;
	case CharacterType::Ring:
		m_renderRect = { m_renderPos.x - 30, m_renderPos.y - 60,
			m_renderPos.x + 30, m_renderPos.y + 22 };

		SetRect({ GetPosition().x - 22, GetPosition().y - 40,
			GetPosition().x + 22, GetPosition().y + 22 });
		m_idleAni->SetImage(L"Image/Character/Mage/Ring_Idle.png");
		m_idleAni->SetFrame(6, 1);
		m_idleAni->SetMotionSpeed(80.0f);

		m_runAni->SetImage(L"Image/Character/Mage/Ring_Run.png");
		m_runAni->SetFrame(6, 1);
		break;
	}
}



void Character::SetState(CharacterState state)
{
	m_state = state;
}

void Character::SetIsSelected(bool isSelected)
{
	mb_isSelected = isSelected;
}

void Character::SetTilePos(POINT pos)
{
	m_tilePos = pos;
}

POINT Character::GetTilePos()
{
	return m_tilePos;
}


bool Character::GetIsSelected()
{
	return mb_isSelected;
}

bool Character::GetIsRangeInMon()
{
	return mb_rangeInMon;
}

CharacterState Character::GetState()
{
	return m_state;
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
