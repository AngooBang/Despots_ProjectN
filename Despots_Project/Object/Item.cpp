#include "Item.h"
#include "stdafx.h"
#include "Component/ImageComponent.h"
#include "Component/TextComponent.h"
#include "Component/ColiderComponent.h"
#include "Manager/GameManager.h"
#include "Manager/CharacterManager.h"
#include "Util/Timer.h"
#include "Util/Input.h"

void Item::Init()
{
	m_itemImg = new ImageComponent(this, 2);
	m_itemImg->SetRect({ GetPosition().x - (ITEM_SIZE_X / 2), GetPosition().y - (ITEM_SIZE_Y / 2),   GetPosition().x + (ITEM_SIZE_X / 2), GetPosition().y + (ITEM_SIZE_Y / 2) });

	m_itemMark = new ImageComponent(this, 2);
	m_itemMark->SetRect({ GetPosition().x - (MARK_SIZE_X / 2), GetPosition().y - (ITEM_SIZE_Y / 2 + 20) - (MARK_SIZE_Y / 2), GetPosition().x + (MARK_SIZE_X / 2), GetPosition().y - (ITEM_SIZE_Y / 2 + 20) + (MARK_SIZE_Y / 2) });

	m_cost = new TextComponent(this, 2);
	m_cost->SetRect({ GetPosition().x - (MARK_SIZE_X / 2), GetPosition().y + (ITEM_SIZE_Y / 2 + 30) - (MARK_SIZE_Y / 2), GetPosition().x + (MARK_SIZE_X / 2), GetPosition().y + (ITEM_SIZE_Y / 2 + 30) + (MARK_SIZE_Y / 2) });
	m_cost->SetBrush(82, 142, 153);
	m_cost->SetFontSize(18);
	m_cost->SetIsKor(true);

	m_itemColider = new ColiderComponent(this, 2, m_itemImg->GetRect(), ColTypes::Item, L"Item");

	SetDataToType();

	GameObject::Init();

}

void Item::Update()
{
	GameObject::Update();
	SetDataToType();
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
			m_itemImg->SetRect({ m_itemImg->GetRect().left, m_itemImg->GetRect().top + m_aniY, m_itemImg->GetRect().right, m_itemImg->GetRect().bottom + m_aniY });

			if (m_aniY >= 3)
				mb_aniHelp = true;

			if (m_aniY <= -3)
				mb_aniHelp = false;

			if (mb_aniHelp)
				m_aniY--;
			else
				m_aniY++;

			m_elapsed = 0.0f;
		}

	}

	//if (Input::GetButtonUp(MK_LBUTTON))
	//{
	//	GameManager::GetInstance()->SetCharType(CharacterType::None);
	//}


}

void Item::OnColision(ColTypes tag)
{
	switch (tag)
	{
	case ColTypes::MouseClickDown:
		if (m_charType == CharacterType::Normal)
		{
			CharacterManager::GetInstance()->AddCharacter();
			break;
		}
		mb_isSelect = true;
		GameManager::GetInstance()->SetCharType(m_charType);
		break;
	case ColTypes::MouseClickUp:
		mb_isSelect = false;

		m_itemImg->SetRect({ GetPosition().x - (ITEM_SIZE_X / 2), GetPosition().y - (ITEM_SIZE_Y / 2),   GetPosition().x + (ITEM_SIZE_X / 2), GetPosition().y + (ITEM_SIZE_Y / 2) });
		m_itemColider->SetRect(m_itemImg->GetRect());

		//GameManager::GetInstance()->SetCharType(CharacterType::None);
		break;
	}
}

void Item::SetDataToType()
{
	switch (m_charType)
	{
	case CharacterType::Normal:
		m_itemMark->SetImage(L"Image/Character/Normal/Normal_Icon.png");

		m_itemImg->SetImage(L"Image/Character/Normal/Normal_Mark.png");

		m_cost->SetText(L"2");
		break;
	case CharacterType::GutSword:
		m_itemMark->SetImage(L"Image/Character/Swordman/Swordman_Icon.png");

		m_itemImg->SetImage(L"Image/Character/Swordman/GutsSword_Mark.png");

		m_cost->SetText(L"8");
		break;
	case CharacterType::Shield:
		m_itemMark->SetImage(L"Image/Character/Tanker/Tanker_Icon.png");

		m_itemImg->SetImage(L"Image/Character/Tanker/Shield_Mark.png");

		m_cost->SetText(L"10");
		break;
	case CharacterType::Crossbow:
		m_itemMark->SetImage(L"Image/Character/Shooter/Shooter_Icon.png");

		m_itemImg->SetImage(L"Image/Character/Shooter/Crossbow_Mark.png");

		m_cost->SetText(L"9");
		break;
	case CharacterType::Ring:
		m_itemMark->SetImage(L"Image/Character/Mage/Mage_Icon.png");

		m_itemImg->SetImage(L"Image/Character/Mage/Ring_Mark.png");

		m_cost->SetText(L"9");
		break;
	}
}

void Item::SetCharType(CharacterType type)
{
	m_charType = type;
}

