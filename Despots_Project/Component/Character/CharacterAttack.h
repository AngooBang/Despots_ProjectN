#pragma once
#include "../Component.h"
#include <queue>

using namespace std;

class Character;
class AnimatorComponent;
class ColiderComponent;
class CharacterAttack : public Component
{
public:
	CharacterAttack(Character* owner, INT32 order = 100) noexcept;
	virtual ~CharacterAttack() noexcept = default;

	virtual void	Init() override;
	virtual void	Update() override;

	void SetIdleAni(AnimatorComponent* idleAni);
	void SetAtkAni(AnimatorComponent* atkAni);
	void SetAtkCol(ColiderComponent* col);

	int GetAtkDamage();

private:
	AnimatorComponent*		m_idleAni = nullptr;
	AnimatorComponent*		m_atkAni = nullptr;
	ColiderComponent*		m_atkCol = nullptr;

	Character*				m_owner = nullptr;

	float					m_attackElapsed = 0.0f;
	float					m_attackSpeed = 1400.0f;
	int						m_attackDamage = 10;

};