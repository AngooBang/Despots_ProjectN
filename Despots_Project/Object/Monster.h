#pragma once
#include "GameObject.h"
#include <stack>

enum class MonsterState { Burrow, Idle, Run, Attack, Hit, Dead, End };

enum class MonsterDir { Left, Right };

enum class MonsterType { Dalek, None };//타입정하고 몬스터만들기~

using namespace std;

class ImageComponent;
class AnimatorComponent;
class CharacterMovement;
class ColiderComponent;
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

	bool GetIsSelected();


	void SetState(MonsterState state);
	void SetIsSelected(bool isSelected);
	void SetTilePos(POINT pos);
	//void SetPath(stack<pair<int, int>> path);
	//void SetDir(MonsterDir dir);


private:
	AnimatorComponent*	m_idleAni = nullptr;
	AnimatorComponent*	m_runAni = nullptr;
	ImageComponent*		m_burrowImg = nullptr;
	ColiderComponent*	m_colider = nullptr;

	MonsterState		m_state = MonsterState::End;

	POINT				m_tilePos = {};
	RECT				m_renderRect = {};


	CharacterMovement*	m_move = nullptr;

	
	MonsterType			m_type = MonsterType::None;
	MonsterDir			m_dir = MonsterDir::Left;
	bool				mb_isSelected = false;

	int					m_hp = 50;
};