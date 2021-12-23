#pragma once
#include "GameObject.h"

class Item;
class Shop : public GameObject
{
public:
	using GameObject::GameObject;

	virtual void Update() override;

	void Show();
	 
	void SetIsAlive(bool isAlive);

private:
	Item* m_item1 = nullptr;
	Item* m_item2 = nullptr;
	Item* m_item3 = nullptr;

	bool mb_isAlive = false;
};
