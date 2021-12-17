#include "Character.h"
#include "stdafx.h"
#include "Component/AnimatorComponent.h"
#include "Component/ImageComponent.h"
#include "Component/Character/CharacterMovement.h"
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

	m_idleAni = new AnimatorComponent(this, 2);
	m_idleAni->SetImage(L"Image/Character/Normal/Normal_Idle.png");
	m_idleAni->SetFrame(6, 1);
	m_idleAni->SetIsLoop(true);
	m_idleAni->SetScale(1.4f);
	m_idleAni->SetIsVisible(true);


	m_runAni = new AnimatorComponent(this, 2);
	m_runAni->SetImage(L"Image/Character/Normal/Normal_Run.png");
	m_runAni->SetFrame(8, 1);
	m_runAni->SetIsLoop(true);
	m_runAni->SetMotionSpeed(50.0f);
	m_runAni->SetScale(1.4f);


	m_selectImg = new ImageComponent(this, 1);
	m_selectImg->SetImage(L"Image/Character/Selected.png");
	m_selectImg->SetIsVisible(false);

	m_colider = new ColiderComponent(this, 2, GetRect(), ColTypes::Character, L"Character");

	m_move = new CharacterMovement(this, 1);


	m_type = CharacterType::Normal;
	m_state = CharacterState::Idle;
	
}

void Character::Update()
{
	SetDataToType();

	GameObject::Update();

	if (mb_isSelected)
		m_selectImg->SetIsVisible(true);
	else  
		m_selectImg->SetIsVisible(false);

	StateUpdate();


	switch (m_dir)
	{
	case CharacterDir::Right:
		// ¿À¸¥ÂÊ º½
		m_idleAni->SetHorizontalReverse(false);
		m_runAni->SetHorizontalReverse(false);
		break;
	case CharacterDir::Left:
		// ¿ÞÂÊ º½
		m_idleAni->SetHorizontalReverse(true);
		m_runAni->SetHorizontalReverse(true);
		break;
	}
	//SetRect({ GetPosition().x - 22, GetPosition().y - 40,
	//		GetPosition().x + 22, GetPosition().y + 22 });
	//selectRc = { selectRc.left + 5 , selectRc.top + 40, selectRc.right - 5, selectRc.bottom - 10 };

	//pos ¸¦ÀÌ¿ëÇÏ¿© Á¶ÀýÇÊ¿ä
	RECT selectRc = { GetPosition().x - 17, GetPosition().y, GetPosition().x + 17, GetPosition().y + 12 };
	m_selectImg->SetRect(selectRc);

	m_idleAni->SetRect(GetRect());
	m_runAni->SetRect(GetRect());
	m_colider->SetRect(GetRect());
	



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
	}
}

void Character::Render()
{
	//ID2D1SolidColorBrush* brush;
	//ImageManagerD2::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkGray), &brush);

	//D2D1_RECT_F rect = { (FLOAT)GetRect().left, (FLOAT)GetRect().top, (FLOAT)GetRect().right, (FLOAT)GetRect().bottom };

	//ImageManagerD2::GetInstance()->GetRenderTarget()->DrawRectangle(rect, brush);
	
	GameObject::Render();
}

void Character::StateUpdate()
{
	switch (m_state)
	{
	case CharacterState::Idle:
		m_idleAni->SetIsVisible(true);
		m_runAni->SetIsVisible(false);
		break;

	case CharacterState::Run:
		m_idleAni->SetIsVisible(false);
		m_runAni->SetIsVisible(true);
		break;

	default:
		break;
	}
}

void Character::SetDataToType()
{
	switch (m_type)
	{
	case CharacterType::Normal:
		SetRect({ GetPosition().x - 22, GetPosition().y - 40,
			GetPosition().x + 22, GetPosition().y + 22 });
		m_idleAni->SetImage(L"Image/Character/Normal/Normal_Idle.png");
		m_idleAni->SetFrame(6, 1);

		m_runAni->SetImage(L"Image/Character/Normal/Normal_Run.png");
		m_runAni->SetFrame(8, 1);
		break;
	case CharacterType::GutSword:
		SetRect({ GetPosition().x - 50, GetPosition().y - 40,
			GetPosition().x + 30, GetPosition().y + 22 });
		m_idleAni->SetImage(L"Image/Character/Swordman/GutsSword_Idle.png");
		m_idleAni->SetFrame(6, 1);

		m_runAni->SetImage(L"Image/Character/Swordman/GutsSword_Run.png");
		m_runAni->SetFrame(12, 1);
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

void Character::SetPath(stack<pair<int, int>> path)
{
	m_move->SetPath(path);
}

void Character::SetDir(CharacterDir dir)
{
	m_dir = dir;
}
