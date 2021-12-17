#pragma once
#include "GameObject.h"

class Item;
class Shop : public GameObject
{
public:
	using GameObject::GameObject;

	virtual void Init() override;
	virtual void Update() override;
private:
	Item* m_item1 = nullptr;
	Item* m_item2 = nullptr;
	Item* m_item3 = nullptr;
	Item* m_item4 = nullptr;
};
