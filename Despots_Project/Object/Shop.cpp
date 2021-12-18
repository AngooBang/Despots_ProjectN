#include "Shop.h"
#include "Object/Item.h"

void Shop::Init()
{
	m_item1 = new Item(GetScene(), GetLayer(), L"Item1");
	m_item2 = new Item(GetScene(), GetLayer(), L"Item2");
	m_item3 = new Item(GetScene(), GetLayer(), L"Item3");
	m_item4 = new Item(GetScene(), GetLayer(), L"Item4");

	m_item1->SetPosition({ 800, 250 });
	m_item2->SetPosition({ 870, 250 });
	m_item3->SetPosition({ 940, 250 });
	m_item4->SetPosition({ 1010, 250 });

	m_item1->SetCharType(CharacterType::Shield);
	m_item2->SetCharType(CharacterType::Crossbow);
	m_item3->SetCharType(CharacterType::GutSword);
	m_item4->SetCharType(CharacterType::Ring);

	m_item1->Init();
	m_item2->Init();
	m_item3->Init();
	m_item4->Init();



	GameObject::Init();
}

void Shop::Update()
{
	GameObject::Update();
}
