#pragma once
#include "GameObject.h"

class Item;
class Shop : public GameObject
{
public:
	using GameObject::GameObject;

	 void Show();

	 void SetVisible(bool isVisible);
private:
	Item* m_item1 = nullptr;
	Item* m_item2 = nullptr;
	Item* m_item3 = nullptr;

	bool mb_isVisible = false;
};
