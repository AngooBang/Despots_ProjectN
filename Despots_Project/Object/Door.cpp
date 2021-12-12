#include "Door.h"
#include "Component/AnimatorComponent.h"
#include "Component/ButtonComponent.h"
#include "Object/TileMap.h"

void Door::Init()
{
	m_pos = GetPosition();
	switch (m_dir)
	{
	case DoorDir::Left:
		m_rect = { m_pos.x, m_pos.y, m_pos.x + 60, m_pos.y + 350 };
		m_doorAni = new AnimatorComponent(this, 1);
		m_doorAni->SetImage(L"Image/Map/Left_Door.png");
		m_doorAni->SetFrame(4, 1);
		m_doorAni->SetRect(m_rect);
		break;
	case DoorDir::Top:
		m_rect = { m_pos.x, m_pos.y, m_pos.x + 260, m_pos.y + 260 };
		m_doorAni = new AnimatorComponent(this, 1);
		m_doorAni->SetImage(L"Image/Map/Up_Open.png");
		m_doorAni->SetFrame(3, 1);
		m_doorAni->SetRect(m_rect);
		break;
	case DoorDir::Right:
		m_rect = { m_pos.x, m_pos.y, m_pos.x + 60, m_pos.y + 350 };
		m_doorAni = new AnimatorComponent(this, 1);
		m_doorAni->SetImage(L"Image/Map/Right_Door.png");
		m_doorAni->SetFrame(4, 1);
		m_doorAni->SetCurrFrame(3);
		m_doorAni->SetRect(m_rect);
		break;
	case DoorDir::Bottom:
		m_rect = { m_pos.x, m_pos.y, m_pos.x + 260, m_pos.y + 260 };
		m_doorAni = new AnimatorComponent(this, 1);
		m_doorAni->SetImage(L"Image/Map/Down_Reveal.png");
		m_doorAni->SetFrame(8, 1);
		m_doorAni->SetRect(m_rect);
		break;
	default:
		break;
	}

	m_button = new ButtonComponent(m_owner, 1, m_owner, &TileMap::MoveLeftRoom);
	m_button->SetCollisionRect(m_rect);

	GameObject::Init();
}

void Door::Update()
{
	switch (m_button->GetButtonState())
	{
	case eButtonState::Idle:
		if (m_dir == DoorDir::Right)
			m_doorAni->Update();
		else
		{
			if (m_dir == DoorDir::Bottom && m_button->GetChangeState())
			{
				m_doorAni->ChangeImg(L"Image/Map/Down_Reveal.png", 8, 1, 8);
				m_button->SetChangeState(false);
			}
			m_doorAni->DownFrame();
		}
		break;
	case eButtonState::Hover:
		if (m_dir == DoorDir::Right)
			m_doorAni->DownFrame();
		else if (m_dir != DoorDir::Top)
			m_doorAni->Update();
		break;
	case eButtonState::Click:
		if (m_dir == DoorDir::Bottom && m_button->GetChangeState())
		{
			m_doorAni->ChangeImg(L"Image/Map/Up_Open.png", 3, 1, 0);
			m_button->SetChangeState(false);
		}
		if (m_dir == DoorDir::Right)
			m_doorAni->DownFrame();
		else
			m_doorAni->Update();
		break;
	default:
		break;
	}
}
