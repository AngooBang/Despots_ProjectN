#pragma once
#include "GameObject.h"

#define HPBAR_WIDTH 20
#define HPBAR_HEIGHT 5
class ImageComponent;
class HpBar : public GameObject
{
public:
	using GameObject::GameObject;

	virtual void Init() override;
	virtual void Update() override;

	void SetFillImg(const wchar_t* path);
	void SetOwner(GameObject* owner);
	void SetMaxHp(int max);
	void SetNowHp(int now);

private:
	GameObject* m_owner = nullptr;

	ImageComponent* m_emptyImg = nullptr;
	ImageComponent* m_fillImg = nullptr;

	int m_maxHp = 0;
	int m_nowHp = 0;


};