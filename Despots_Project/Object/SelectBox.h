#pragma once
#include "GameObject.h"
class ImageComponent;
class SelectBox : public GameObject
{
public:
	using GameObject::GameObject;

	virtual void Init() override;
	virtual void Update() override;

private:
	ImageComponent* m_img = nullptr;
	POINT m_clickPos = {};
};