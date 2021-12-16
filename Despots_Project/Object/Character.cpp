#include "Character.h"
#include "stdafx.h"
#include "Component/AnimatorComponent.h"
#include "Component/ImageComponent.h"
#include "Component/Character/CharacterMovement.h"

Character::Character(Scene* scene, Layer* layer, const std::wstring& tag, POINT pos)
	:GameObject(scene, layer, tag)
{
	SetPosition(pos);
}

void Character::Init()
{

	m_idleAni = new AnimatorComponent(this, 2);
	m_idleAni->SetImage(L"Image/Character/Normal/Normal_Idle.png");
	m_idleAni->SetFrame(6, 1);
	m_idleAni->SetIsLoop(true);

	m_selectImg = new ImageComponent(this, 1);
	m_selectImg->SetImage(L"Image/Character/Selected.png");

	m_selectImg->SetIsVisible(false);

	m_move = new CharacterMovement(this, 1);


	m_state = CharacterState::Idle;
	
}

void Character::Update()
{
	if (mb_isSelected)
		m_selectImg->SetIsVisible(true);
	else
		m_selectImg->SetIsVisible(false);

	SetRect({ GetPosition().x - 30, GetPosition().y - 60,
			GetPosition().x + 30, GetPosition().y + 20 });
	RECT selectRc = GetRect();
	selectRc = { selectRc.left + 10 , selectRc.top + 50, selectRc.right - 10, selectRc.bottom - 15 };
	m_selectImg->SetRect(selectRc);

	m_idleAni->SetRect(GetRect());

	GameObject::Update();
}

void Character::Render()
{
	ID2D1SolidColorBrush* brush;
	ImageManagerD2::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkGray), &brush);

	D2D1_RECT_F rect = { (FLOAT)GetRect().left, (FLOAT)GetRect().top, (FLOAT)GetRect().right, (FLOAT)GetRect().bottom };

	ImageManagerD2::GetInstance()->GetRenderTarget()->DrawRectangle(rect, brush);
	
	GameObject::Render();
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
