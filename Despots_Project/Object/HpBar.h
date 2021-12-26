#pragma once
#include "GameObject.h"

class ImageComponent;
class HpBar : public GameObject
{
public:
	using GameObject::GameObject;

	virtual void Init() override;
	virtual void Update() override;

	void SetFillImg(const wchar_t* path);
	void SetOwner(GameObject* owner);

	void SetWidth(int width);
	void SetHeight(int height);
	void SetDistance(int dist);
	void SetMaxHp(int max);
	void SetNowHp(int now);

private:
	GameObject* m_owner = nullptr;

	ImageComponent* m_emptyImg = nullptr;
	ImageComponent* m_fillImg = nullptr;

	int m_width = 25;
	int m_height = 5;

	int m_dist = 10;

	int m_maxHp = 0;
	int m_nowHp = 0;


};