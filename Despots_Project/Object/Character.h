#pragma once
#include "GameObject.h"

class AnimatorComponent;
class Character : public GameObject
{
public:
	Character(Scene* scene, Layer* layer, const std::wstring& tag, POINT pos);

	virtual void Init() override;

private:
	AnimatorComponent* m_idleAni = nullptr;
};