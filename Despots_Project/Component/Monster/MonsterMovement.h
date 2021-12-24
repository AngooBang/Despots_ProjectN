#pragma once
#include "../Component.h"
#include <queue>

using namespace std;

class Monster;
class MonsterMovement : public Component
{
public:
	MonsterMovement(Monster* owner, INT32 order = 100) noexcept;
	virtual ~MonsterMovement() noexcept = default;

	virtual void	Update() override;

	void			Move();
	void			SetPath(deque<POINT> path);
	void			SetIsMove(bool isMove);

	bool			GetIsMove();
private:
	float					m_speed = 200.0f;

	Monster* m_owner = nullptr;
	deque<POINT>			m_path;

	bool					mb_isMove = false;
};