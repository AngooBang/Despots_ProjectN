#pragma once
#include "GameObject.h"
#include <queue>

enum class CharacterState { Idle, Run, Attack, Hit, Fly, Dead, End };

enum class CharacterDir { Left, Right };

enum class CharacterType { Normal, GutSword, Crossbow, Shield, Ring, None };

#define NORMAL_HP 80
#define NORMAL_ATK_RANGE -5
#define NORMAL_ATK_DMG 5
#define NORMAL_ATK_SPEED 2.0f

#define GUTS_HP 200
#define GUTS_ATK_RANGE 20
#define GUTS_ATK_DMG 40
#define GUTS_ATK_SPEED 3.0f

#define SHIELD_HP 400
#define SHIELD_ATK_RANGE 5
#define SHIELD_ATK_DMG 15
#define SHIELD_ATK_SPEED 3.0f

#define CROSSBOW_HP 150
#define CROSSBOW_ATK_RANGE 200
#define CROSSBOW_ATK_DMG 20
#define CROSSBOW_ATK_SPEED 2.5f

#define RING_HP 60
#define RING_ATK_RANGE 300
#define RING_ATK_DMG 40
#define RING_ATK_SPEED 5.0f

using namespace std;

class ImageComponent;
class AnimatorComponent;
class CharacterMovement;
class CharacterAttack;
class ColiderComponent;
class Monster;
class HpBar;
class Character : public GameObject
{
public:
	Character(Scene* scene, Layer* layer, const std::wstring& tag, POINT pos);

	virtual void Init() override;
	virtual void Update() override;
	virtual void OnColision(ColTypes tag) override;
	virtual void OnColision(ColiderComponent* col1, ColiderComponent* col2) override;
	virtual void Render() override;

	void FlySavePos();

	void StateUpdate();

	void SetDataToType();

	// 상태세터만들기

	POINT GetTilePos();
	POINT GetStanbyPos();

	bool GetIsSelected();
	bool GetIsRangeInMon();
	bool GetIsAlive();
	bool GetIsMove();
	CharacterState GetState();
	CharacterDir GetDir();
	CharacterType GetCType();
	Monster* GetTarget();
	POINT GetRenderRect();


	void SetState(CharacterState state);
	void SetIsSelected(bool isSelected);
	void SetTilePos(POINT pos);
	void SetStanbyPos(POINT pos);
	void SetPath(deque<POINT> path);
	void SetDir(CharacterDir dir);
	void SetTarget(Monster* target);


private:
	AnimatorComponent*	m_flyAni = nullptr;
	AnimatorComponent*	m_idleAni = nullptr;
	AnimatorComponent*	m_runAni = nullptr;
	AnimatorComponent*	m_attackAni = nullptr;
	AnimatorComponent*	m_deathAni = nullptr;

	ImageComponent*		m_selectImg = nullptr;
	ColiderComponent*	m_colider = nullptr;
	ColiderComponent*	m_atkRangeCol = nullptr;
	ColiderComponent*	m_atkCol = nullptr;

	CharacterState		m_state = CharacterState::End;

	Monster*			m_target = nullptr;
	HpBar*				 m_hpBar = nullptr;
	

	POINT m_tilePos = {};

	POINT m_stanbyPos = {};

	LONG m_flyDestY = NULL;

	POINT m_renderPos = {};
	RECT m_renderRect = {};


	CharacterMovement*	m_moveComp = nullptr;
	CharacterAttack*	m_atkComp = nullptr;

	CharacterType		m_type = CharacterType::None;
	CharacterDir		m_dir = CharacterDir::Right;
	bool				mb_isSelected = false;
	bool				mb_isVisible = true;
	bool				mb_rangeInMon = false;
	bool				mb_isAlive = true;

	bool				mb_isClassChanged = false;
	int					m_hp = 0;
};
