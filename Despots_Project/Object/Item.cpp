#include "Item.h"
#include "stdafx.h"
#include "Component/ImageComponent.h"
#include "Component/TextComponent.h"
#include "Component/ColiderComponent.h"
#include "Manager/GameManager.h"
#include "Util/Timer.h"
#include "Util/Input.h"

void Item::Init()
{
	m_itemImg = new ImageComponent(this, 2);
	m_itemImg->SetImage(L"Image/Character/Swordman/GutsSword_Mark.png");
	m_itemImg->SetRect({ GetPosition().x - (ITEM_SIZE_X / 2), GetPosition().y - (ITEM_SIZE_Y / 2),   GetPosition().x + (ITEM_SIZE_X / 2), GetPosition().y + (ITEM_SIZE_Y / 2) });

	m_itemMark = new ImageComponent(this, 2);
	m_itemMark->SetImage(L"Image/Character/Swordman/Swordman_Mark.png");
	m_itemMark->SetRect({ GetPosition().x - (MARK_SIZE_X / 2), GetPosition().y - (ITEM_SIZE_Y / 2 + 20) - (MARK_SIZE_Y / 2), GetPosition().x + (MARK_SIZE_X / 2), GetPosition().y - (ITEM_SIZE_Y / 2 + 20) + (MARK_SIZE_Y / 2) });

	m_cost = new TextComponent(this, 2);
	m_cost->SetText(L"8");
	m_cost->SetRect({ GetPosition().x - (MARK_SIZE_X / 2), GetPosition().y + (ITEM_SIZE_Y / 2 + 30) - (MARK_SIZE_Y / 2), GetPosition().x + (MARK_SIZE_X / 2), GetPosition().y + (ITEM_SIZE_Y / 2 + 30) + (MARK_SIZE_Y / 2) });
	m_cost->SetBrush(82, 142, 153);
	m_cost->SetFontSize(18);
	m_cost->SetIsKor(true);

	m_itemColider = new ColiderComponent(this, 2, m_itemImg->GetRect(), ColTypes::Item, L"Item1");


	GameObject::Init();

}

void Item::Update()
{
	static int y = 0;
	static bool b = false;
	if (mb_isSelect)
	{
		POINT mouse = Input::GetMousePosition();
		m_itemImg->SetRect({ mouse.x - (ITEM_SIZE_X / 2), mouse.y - (ITEM_SIZE_Y / 2),  mouse.x + (ITEM_SIZE_X / 2), mouse.y + (ITEM_SIZE_Y / 2) });
		m_itemColider->SetRect(m_itemImg->GetRect());

	}
	else
	{
		m_elapsed += Timer::GetDeltaTime();
		if (m_elapsed >= 100.0f)
		{
			m_itemImg->SetRect({ m_itemImg->GetRect().left, m_itemImg->GetRect().top + y, m_itemImg->GetRect().right, m_itemImg->GetRect().bottom + y });

			if (y >= 3)
				b = true;

			if (y <= -3)
				b = false;

			if (b)
				y--;
			else
				y++;

			m_elapsed = 0.0f;
		}

	}


	GameObject::Update();
}

void Item::OnColision(ColTypes tag)
{
	switch (tag)
	{
	case ColTypes::MouseClickDown:
		mb_isSelect = true;
		GameManager::GetInstance()->SetCharType(m_charType);
		break;
	case ColTypes::MouseClickUp:
		mb_isSelect = false;

		m_itemImg->SetRect({ GetPosition().x - (ITEM_SIZE_X / 2), GetPosition().y - (ITEM_SIZE_Y / 2),   GetPosition().x + (ITEM_SIZE_X / 2), GetPosition().y + (ITEM_SIZE_Y / 2) });
		m_itemColider->SetRect(m_itemImg->GetRect());

		GameManager::GetInstance()->SetCharType(CharacterType::None);
		break;
	}
}

