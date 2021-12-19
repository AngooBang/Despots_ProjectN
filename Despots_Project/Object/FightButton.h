#pragma once
#include "GameObject.h"

#define FIGHTBTN_POS_X 1200
#define FIGHTBTN_POS_Y 680

#define FIGHTBTN_SIZE_X 140
#define FIGHTBTN_SIZE_Y 60

class ImageComponent;
class ColiderComponent;
template <typename T>
class ButtonComponent;
class FightButton : public GameObject
{
public:
	using ButtonComponent = ButtonComponent<FightButton>;
	using GameObject::GameObject;

	virtual void Init() override;
	virtual void Update() override;
	//virtual void OnColision(ColTypes type) override;

	void BattleStart();
private:
	ImageComponent* m_idleImg = nullptr;
	ImageComponent* m_hoverImg = nullptr;
	ImageComponent* m_clickImg = nullptr;

	ButtonComponent* m_buttonComp = nullptr;
	//ColiderComponent* m_colider = nullptr;
};