#pragma once
#include "GameObject.h"
class ImageComponent;
class MoveFrame : public GameObject
{
public:
	using GameObject::GameObject;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
private:
	ImageComponent* m_img;
};