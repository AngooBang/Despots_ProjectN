#pragma once
#include "GameObject.h"
#include <stack>

enum class CharacterState { Idle, Run, Attack, Hit, Fly, End };

enum class CharacterDir { Left, Right };

enum class CharacterType { Normal, GutSword, Crossbow, Shield, Ring, None };

using namespace std;

class ImageComponent;
class AnimatorComponent;
class CharacterMovement;
class ColiderComponent;
class Tile;
class Character : public GameObject
{
public:
	Character(Scene* scene, Layer* layer, const std::wstring& tag, POINT pos);

	virtual void Init() override;
	virtual void Update() override;
	virtual void OnColision(ColTypes tag) override;
	virtual void Render() override;


	void StateUpdate();

	void SetDataToType();

	// 상태세터만들기

	POINT GetTilePos();

	bool GetIsSelected();


	void SetState(CharacterState state);
	void SetIsSelected(bool isSelected);
	void SetTilePos(POINT pos);
	void SetPath(stack<pair<int, int>> path);
	void SetDir(CharacterDir dir);


private:
	AnimatorComponent*	m_idleAni = nullptr;
	AnimatorComponent*	m_runAni = nullptr;
	ImageComponent*		m_selectImg = nullptr;
	ColiderComponent*	m_colider = nullptr;

	CharacterState		m_state = CharacterState::End;
	
	POINT m_tilePos = {};
	RECT m_renderRect = {};


	CharacterMovement* m_move = nullptr;

	CharacterType		m_type = CharacterType::None;
	CharacterDir		m_dir = CharacterDir::Right;
	bool				mb_isSelected = false;
};