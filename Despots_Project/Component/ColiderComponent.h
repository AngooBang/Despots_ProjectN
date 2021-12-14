#pragma once
#include "Component.h"
#include <string>

enum class ColTypes { Character, Monster, Door, MouseHover, MouseClick, None };

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

	void SetShape(RECT rect);
	RECT GetShape();

	GameObject* GetOwner();

private:
	RECT m_colRect = {};
	ColTypes m_type = ColTypes::None;
	std::wstring m_tag = L"";
};