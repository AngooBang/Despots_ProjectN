#pragma once
#include "Component.h"
#include <string>

enum class ColTypes { Character, Monster, Door, MouseHover, MouseClickDown, MouseClickUp, Item, None };

class ColiderComponent : public Component
{

public:

	ColiderComponent(GameObject* owner, INT32 order, RECT rect, ColTypes type, const std::wstring& tag);
	//using Component::Component;
	virtual ~ColiderComponent() noexcept = default;


	//virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	ColTypes GetType();
	std::wstring GetTag();

	void SetRect(RECT rect);
	RECT GetRect();

	GameObject* GetOwner();

private:
	RECT m_colRect = {};
	ColTypes m_type = ColTypes::None;
	std::wstring m_tag = L"";
};