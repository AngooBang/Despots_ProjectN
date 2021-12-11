#pragma once
#include "GameObject.h"


class TextComponent;
class ImageComponent;
template <typename T>
class ButtonComponent;
class ExitButton : public GameObject
{
public:
	using ButtonComponent = ButtonComponent<ExitButton>;
	using GameObject::GameObject;

	virtual void Init() override;
	virtual void Update() override;

	void GameExit();
private:
	ImageComponent* m_hoverImg = nullptr;
	ImageComponent* m_clickImg = nullptr;

	ButtonComponent* m_buttonComp = nullptr;
	TextComponent* m_textComp = nullptr;
};