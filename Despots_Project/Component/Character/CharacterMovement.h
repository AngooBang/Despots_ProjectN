#pragma once
#include "../Component.h"
#include <queue>

using namespace std;

class Character;
class CharacterMovement : public Component
{
public:
	CharacterMovement(Character* owner, INT32 order = 100) noexcept;
	virtual ~CharacterMovement() noexcept = default;

	virtual void	Update() override;

	void			Move();
	void			SetPath(deque<POINT> path);
	void			SetIsMove(bool isMove);
private:
	float					m_speed = 200.0f;

	Character*				m_owner = nullptr;
	deque<POINT>			m_path;

	bool					mb_isMove = false;
};