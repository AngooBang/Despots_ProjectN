#include "Door.h"
#include "Component/AnimatorComponent.h"
#include "Manager/ColiderManager.h"
#include "Manager/GameManager.h"
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
		m_colider = new ColiderComponent(this, 1, LDOOR_COL_RECT, ColTypes::Door, L"LDoor");
		break;
	case DoorDir::Top:
		m_rect = { m_pos.x, m_pos.y, m_pos.x + 260, m_pos.y + 260 };
		m_doorAni = new AnimatorComponent(this, 1);
		m_doorAni->SetImage(L"Image/Map/Up_Open.png");
		m_doorAni->SetFrame(3, 1);
		m_doorAni->SetRect(m_rect);
		m_colider = new ColiderComponent(this, 1, TDOOR_COL_RECT, ColTypes::Door, L"TDoor");
		break;
	case DoorDir::Right:
		m_rect = { m_pos.x, m_pos.y, m_pos.x + 60, m_pos.y + 350 };
		m_doorAni = new AnimatorComponent(this, 1);
		m_doorAni->SetImage(L"Image/Map/Right_Door.png");
		m_doorAni->SetFrame(4, 1);
		m_doorAni->SetCurrFrame(3);
		m_doorAni->SetRect(m_rect);
		m_colider = new ColiderComponent(this, 1, RDOOR_COL_RECT, ColTypes::Door, L"RDoor");
		break;
	case DoorDir::Bottom:
		m_rect = { m_pos.x, m_pos.y, m_pos.x + 260, m_pos.y + 260 };
		m_doorAni = new AnimatorComponent(this, 1);
		m_doorAni->SetImage(L"Image/Map/Down_Reveal.png");
		m_doorAni->SetFrame(8, 1);
		m_doorAni->SetRect(m_rect);
		m_colider = new ColiderComponent(this, 1, BDOOR_COL_RECT, ColTypes::Door, L"BDoor");
		break;
	default:
		break;
	}


	GameObject::Init();
}

void Door::Update()
{
	if (m_state == DoorState::Hover || m_state == DoorState::Click)
	{
		m_state = DoorState::Idle;
		mb_chageState = true;
	}

	GameObject::Update();

	if (m_state == DoorState::Idle)
	{
		//mb_chageState = true;
		//idle일때 해야할 일들.
		switch (m_dir)
		{
		case DoorDir::Left:
			m_doorAni->SetIsReverse(true);
			break;
		case DoorDir::Top:
			m_doorAni->SetIsReverse(true);
			break;
		case DoorDir::Right:
			m_doorAni->SetIsReverse(false);
			break;
		case DoorDir::Bottom:
			if (mb_chageState)
			{
				m_doorAni->ChangeImg(L"Image/Map/Down_Reveal.png", 8, 1, 7);
				m_doorAni->SetIsReverse(true);
				mb_chageState = false;
			}
			break;
		}
	}



	

}

void Door::OnColision(ColTypes tag)
{
	switch (tag)
	{
	case ColTypes::MouseHover:
		m_state = DoorState::Hover;
		mb_chageState = true;
		switch (m_dir)
		{
		case DoorDir::Left:
			m_doorAni->SetIsReverse(false);
			break;
		case DoorDir::Top:
			break;
		case DoorDir::Right:
			m_doorAni->SetIsReverse(true);
			break;
		case DoorDir::Bottom:
			m_doorAni->SetIsReverse(false);
			break;
		}
		break;
	case ColTypes::MouseClickDown:
		if (GameManager::GetInstance()->GetGameState() != GameState::EndBattle) break;
		m_state = DoorState::Click;
		mb_chageState = true;
		switch (m_dir)
		{
		case DoorDir::Left:
			if (m_owner->GetRoomNum() == 1)
				m_owner->SetMoveRoom(DoorDir::Left);
			break;
		case DoorDir::Top:
			m_doorAni->SetIsReverse(false);
			if (m_owner->GetRoomNum() == 1)
				m_owner->SetMoveRoom(DoorDir::Top);
			break;
		case DoorDir::Right:
			if (m_owner->GetRoomNum() == 1)
				m_owner->SetMoveRoom(DoorDir::Right);
			break;
		case DoorDir::Bottom:
			if (mb_chageState)
			{
				m_doorAni->ChangeImg(L"Image/Map/Up_Open.png", 3, 1, 0);
				mb_chageState = false;
			}
			if(m_owner->GetRoomNum() == 1)
				m_owner->SetMoveRoom(DoorDir::Bottom);
			break;
		}
		break;
	default:
		break;
	}
}

void Door::Render()
{
	if (mb_isVisible == false) return;

	GameObject::Render();
}

void Door::SetIsVisible(bool isVisible)
{
	mb_isVisible = isVisible;
}


