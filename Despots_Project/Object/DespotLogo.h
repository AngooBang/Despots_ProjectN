#pragma once
#include "GameObject.h"
class DespotLogo : public GameObject
{
public:
	using GameObject::GameObject;

	virtual void Init() override;
};