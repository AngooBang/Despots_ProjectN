#pragma once
#include "../Component.h"
#include <stack>

using namespace std;

class Character;
class CharacterMovement : public Component
{
public:
	CharacterMovement(Character* owner, INT32 order = 100) noexcept;
	virtual ~CharacterMovement() noexcept = default;

	virtual void	Update() override;

	void			Move();
	void			SetPath(stack<pair<int, int>> path);
private:
	float					m_speed = 0.2f;

	Character*				m_owner = nullptr;
	stack<pair<int, int>>	m_path;

	bool					mb_isMove = false;
};