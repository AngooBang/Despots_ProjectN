#pragma once
#include "Component.h"
#include <string>

enum class ColTypes { Character, CAtkRange, CAtk, Monster, Door, MouseHover, MouseClickDown, MouseClickUp, Item, Button, None };

class CharacterAttack;
class ColiderComponent : public Component
{

public:

	ColiderComponent(GameObject* owner, INT32 order, RECT rect, ColTypes type, const std::wstring& tag);
	//using Component::Component;
	virtual ~ColiderComponent() noexcept = default;


	//virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;


	void SetIsAlive(bool isAlive);
	void SetRect(RECT rect);
	void SetCAtkComp(CharacterAttack* cAtkComp);

	std::wstring GetTag();
	ColTypes GetType();
	RECT GetRect();
	CharacterAttack* GetCAtkComp();
	bool GetIsAlive();

	GameObject* GetOwner();

private:
	RECT m_colRect = {};
	ColTypes m_type = ColTypes::None;
	std::wstring m_tag = L"";
	CharacterAttack* m_cAtkComp = nullptr;
	

	bool mb_isAlive = true;
};