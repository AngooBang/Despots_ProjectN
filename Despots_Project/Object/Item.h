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
	virtual void Render() override;


	void SetIsAlive(bool isAlive);
	void SetDataToType();

	void SetCharType(CharacterType type);

private:

	ImageComponent* m_itemImg = nullptr;
	ImageComponent* m_itemMark = nullptr; 

	ColiderComponent* m_itemColider = nullptr;
	TextComponent* m_cost = nullptr;

	CharacterType m_charType = CharacterType::None;
	float m_elapsed = 0.0f;

	int m_aniY = 0;
	bool mb_aniHelp = false;

	bool mb_isSelect = false;

	bool mb_isAlive = true;
};