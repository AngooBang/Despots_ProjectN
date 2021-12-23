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

	virtual void	Update() override;

	void ShotColider();

	void SetIdleAni(AnimatorComponent* idleAni);
	void SetAtkAni(AnimatorComponent* atkAni);
	void SetAtkCol(ColiderComponent* col);

	void SetAttackDamage(int damage);
	void SetAttackSpeed(float speed);
	void SetAttackRange(int range);

	void SetIsCloseRange(bool closeRange);
	void SetBulletSize(int size);


	int GetAtkDamage();
	int GetAtkRange();
private:
	AnimatorComponent*		m_idleAni = nullptr;
	AnimatorComponent*		m_atkAni = nullptr;
	ColiderComponent*		m_atkCol = nullptr;

	Character*				m_owner = nullptr;

	float					m_attackElapsed = 0.0f;
	float					m_attackSpeed = 1.4f;
	int						m_attackDamage = 10;
	int						m_attackRange = 10;

	int						m_bulletSize = 0;

	bool					mb_isCloseRange = true;

};