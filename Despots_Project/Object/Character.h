#pragma once
#include "GameObject.h"
#include <queue>

enum class CharacterState { Idle, Run, Attack, Hit, Fly, End };

enum class CharacterDir { Left, Right };

enum class CharacterType { Normal, GutSword, Crossbow, Shield, Ring, None };


#define NORMAL_ATK_RANGE 10

using namespace std;

class ImageComponent;
class AnimatorComponent;
class CharacterMovement;
class CharacterAttack;
class ColiderComponent;
class Monster;
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

	bool GetIsSelected();
	bool GetIsRangeInMon();
	CharacterState GetState();


	void SetState(CharacterState state);
	void SetIsSelected(bool isSelected);
	void SetTilePos(POINT pos);
	void SetPath(deque<POINT> path);
	void SetDir(CharacterDir dir);
	void SetTarget(Monster* target);


private:
	AnimatorComponent*	m_flyAni = nullptr;
	AnimatorComponent*	m_idleAni = nullptr;
	AnimatorComponent*	m_runAni = nullptr;
	AnimatorComponent*	m_attackAni = nullptr;

	ImageComponent*		m_selectImg = nullptr;
	ColiderComponent*	m_colider = nullptr;
	ColiderComponent*	m_atkRangeCol = nullptr;
	ColiderComponent*	m_atkCol = nullptr;

	int					m_atkRange = NULL;

	CharacterState		m_state = CharacterState::End;

	Monster*			m_target = nullptr;
	
	POINT m_tilePos = {};
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
};
