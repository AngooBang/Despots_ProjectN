#pragma once
#include "GameObject.h"
#include <stack>

enum class CharacterState { Idle, Move, Attack, Hit, Fly, End };

using namespace std;

class ImageComponent;
class AnimatorComponent;
class CharacterMovement;
class Tile;
class Character : public GameObject
{
public:
	Character(Scene* scene, Layer* layer, const std::wstring& tag, POINT pos);

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void SetIsSelected(bool isSelected);

	void SetTilePos(POINT pos);

	POINT GetTilePos();

	bool GetIsSelected();

	void SetPath(stack<pair<int, int>> path);


private:
	AnimatorComponent*	m_idleAni = nullptr;
	ImageComponent*		m_selectImg = nullptr;

	CharacterState		m_state = CharacterState::End;
	
	POINT m_tilePos = {};

	CharacterMovement* m_move = nullptr;

	bool				mb_isSelected = false;
};