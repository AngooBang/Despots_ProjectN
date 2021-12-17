#pragma once
#include "GameObject.h"
#include "Object/Character.h"

#define ITEM_SIZE_X 50
#define ITEM_SIZE_Y 50

#define MARK_SIZE_X 20
#define MARK_SIZE_Y 20

class ColiderComponent;
class TextComponent;
class ImageComponent;
class Item : public GameObject
{
public:
	using GameObject::GameObject;

	virtual void Init() override;
	virtual void Update() override;
	virtual void OnColision(ColTypes tag) override;

private:

	ImageComponent* m_itemImg = nullptr;
	ImageComponent* m_itemMark = nullptr;

	ColiderComponent* m_itemColider = nullptr;
	TextComponent* m_cost = nullptr;

	CharacterType m_charType = CharacterType::GutSword;
	float m_elapsed = 0.0f;
	bool mb_isSelect = false;
};