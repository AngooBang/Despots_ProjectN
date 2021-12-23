#include "Shop.h"
#include "stdafx.h"
#include "Object/Item.h"
#include "Scene/Layer.h"

void Shop::Update()
{
	if (!mb_isAlive && m_item1 != nullptr)
	{
		m_item1->SetIsAlive(false);
		m_item2->SetIsAlive(false);
		m_item3->SetIsAlive(false);
		return;
	}
	GameObject::Update();
}

void Shop::Show()
{
	GetLayer()->RemoveObject(L"Item");
	if (m_item1 != nullptr)
	{
		SAFE_RELEASE(m_item1);
	}
	if (m_item2 != nullptr)
	{
		SAFE_RELEASE(m_item2);
	}
	if (m_item3 != nullptr)
	{
		SAFE_RELEASE(m_item3);
	}
	
	m_item1 = new Item(GetScene(), GetLayer(), L"Item");
	m_item2 = new Item(GetScene(), GetLayer(), L"Item");
	m_item3 = new Item(GetScene(), GetLayer(), L"Item");

	m_item1->SetPosition({ 800, 250 });
	m_item2->SetPosition({ 870, 250 });
	m_item3->SetPosition({ 940, 250 });

	int ran = rand() % 4;
	switch (ran)
	{
	case 0:
		m_item1->SetCharType(CharacterType::Shield);
		break;
	case 1:
		m_item1->SetCharType(CharacterType::GutSword);
		break;
	case 2:
		m_item1->SetCharType(CharacterType::Crossbow);
		break;
	case 3:
		m_item1->SetCharType(CharacterType::Ring);
		break;
	}

	ran = rand() % 4;
	switch (ran)
	{
	case 0:
		m_item2->SetCharType(CharacterType::Shield);
		break;
	case 1:
		m_item2->SetCharType(CharacterType::GutSword);
		break;
	case 2:
		m_item2->SetCharType(CharacterType::Crossbow);
		break;
	case 3:
		m_item2->SetCharType(CharacterType::Ring);
		break;
	}

	m_item3->SetCharType(CharacterType::Normal);

	m_item1->Init();
	m_item2->Init();
	m_item3->Init();

	mb_isAlive = true;

}

void Shop::SetIsAlive(bool isAlive)
{
	mb_isAlive = isAlive;
}


