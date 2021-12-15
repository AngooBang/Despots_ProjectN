#include "Character.h"
#include "Component/AnimatorComponent.h"
#include "Component/ImageComponent.h"

Character::Character(Scene* scene, Layer* layer, const std::wstring& tag, POINT pos)
	:GameObject(scene, layer, tag)
{
	SetPosition(pos);
}

void Character::Init()
{
	SetRect({ GetPosition().x, GetPosition().y - 30,
			GetPosition().x + 50, GetPosition().y + 50 });

	m_idleAni = new AnimatorComponent(this, 2);
	m_idleAni->SetImage(L"Image/Character/Normal/Normal_Idle.png");
	m_idleAni->SetFrame(6, 1);
	m_idleAni->SetIsLoop(true);
	m_idleAni->SetRect(GetRect());

	m_selectImg = new ImageComponent(this, 1);
	m_selectImg->SetImage(L"Image/Character/Selected.png");
	RECT selectRc = GetRect();
	selectRc = { selectRc.left + 10 , selectRc.top + 50, selectRc.right - 10, selectRc.bottom - 15 };
	m_selectImg->SetRect(selectRc);
	m_selectImg->SetIsVisible(false);
	
}

void Character::Update()
{
	if (mb_isSelected)
		m_selectImg->SetIsVisible(true);
	else
		m_selectImg->SetIsVisible(false);


	GameObject::Update();
}

void Character::SetTile(Tile* tile)
{
	m_seatTile = tile;
}

void Character::SetIsSelected(bool isSelected)
{
	mb_isSelected = isSelected;
}

Tile* Character::GetTile()
{
	return m_seatTile;
}

bool Character::GetIsSelected()
{
	return mb_isSelected;
}
