#pragma once
#include "GameObject.h"
#include <stack>

enum class MonsterState { Burrow, Idle, Run, Attack, Hit, Dead, End };

enum class MonsterDir { Left, Right };

enum class MonsterType { Dalek, None };//타입정하고 몬스터만들기~


#define DALEK_ATK_DMG 20
#define DALEK_ATK_SPEED 4.0f
#define DALEK_ATK_RANGE 200

#define DALEK_HP 200



using namespace std;

class ImageComponent;
class AnimatorComponent;
class MonsterMovement;
class MonsterAttack;
class ColiderComponent;
class Character;
class HpBar;
class Monster : public GameObject
{
public:
	Monster(Scene* scene, Layer* layer, const std::wstring& tag, POINT pos);

	virtual void Init() override;
	virtual void Update() override;
	virtual void OnColision(ColiderComponent* col1, ColiderComponent* col2) override;
	virtual void Render() override;


	void StateUpdate();

	void SetDataToType();

	// 상태세터만들기

	POINT GetTilePos();
	MonsterType GetMType();
	MonsterState GetState();
	MonsterDir GetDir();
	Character* GetTarget();

	bool GetIsSelected();
	bool GetIsAlive();
	bool GetRangeInChar();
	bool GetIsMove();

	void SetTarget(Character* target);
	void SetState(MonsterState state);
	void SetIsSelected(bool isSelected);
	void SetTilePos(POINT pos);

	void SetPath(deque<POINT> path);
	void SetDir(MonsterDir dir);


private:
	AnimatorComponent*	m_idleAni = nullptr;
	AnimatorComponent*	m_runAni = nullptr;
	AnimatorComponent*	m_attackAni = nullptr;
	AnimatorComponent*	m_deathAni = nullptr;

	ImageComponent*		m_burrowImg = nullptr;
	ColiderComponent*	m_colider = nullptr;
	ColiderComponent*	m_atkRangeCol = nullptr;
	ColiderComponent*	m_atkCol = nullptr;

	HpBar*				m_hpBar = nullptr;

	MonsterState		m_state = MonsterState::End;

	POINT				m_tilePos = {};
	RECT				m_renderRect = {};


	MonsterMovement*	m_moveComp = nullptr;
	MonsterAttack*		m_atkComp = nullptr;

	Character*			m_target = nullptr;
	
	MonsterType			m_type = MonsterType::None;
	MonsterDir			m_dir = MonsterDir::Left;
	bool				mb_isSelected = false;
	bool				mb_isAlive = true;
	bool				mb_rangeInChar = false;

	int					m_hp = 0;
};