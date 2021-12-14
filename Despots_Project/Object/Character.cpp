#include "Character.h"
#include "Component/AnimatorComponent.h"

Character::Character(Scene* scene, Layer* layer, const std::wstring& tag, POINT pos)
	:GameObject(scene, layer, tag)
{
	SetPosition(pos);
}

void Character::Init()
{
	SetRect({ GetPosition().x - 25, GetPosition().y - 30,
			GetPosition().x + 25, GetPosition().y + 50 });

	m_idleAni = new AnimatorComponent(this, 1);
	m_idleAni->SetImage(L"Image/Character/Normal/Normal_Idle.png");
	m_idleAni->SetFrame(6, 1);
	m_idleAni->SetIsLoop(true);
	m_idleAni->SetRect(GetRect());
}
