#pragma once
#include "GameObject.h"
class BackGround : public GameObject
{
public:
	using GameObject::GameObject;

	virtual void Init() override;
};