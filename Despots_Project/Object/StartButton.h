#pragma once
#include "GameObject.h"

class ImageComponent;
template <typename T>
class ButtonComponent;
class StartButton : public GameObject
{
public:
	using ButtonComponent = ButtonComponent<StartButton>;
	using GameObject::GameObject;

	virtual void Init() override;
	virtual void Update() override;

	void GameStart();
private:
	ImageComponent* m_hoverImg = nullptr;
	ImageComponent* m_clickImg = nullptr;

	ButtonComponent* m_buttonComp = nullptr;
};