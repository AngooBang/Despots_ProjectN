#pragma once
#include "../Component.h"
#include <queue>

using namespace std;

class Monster;
class AnimatorComponent;
class ColiderComponent;
class MonsterAttack : public Component
{
public:
	MonsterAttack(Monster* owner, INT32 order = 100) noexcept;
	virtual ~MonsterAttack() noexcept = default;

	virtual void	Update() override;

	void SetShotData();
	void ShotColider();

	void SetIdleAni(AnimatorComponent* idleAni);
	void SetAtkAni(AnimatorComponent* atkAni);
	void SetAtkCol(ColiderComponent* col);

	void SetAttackDamage(int damage);
	void SetAttackSpeed(float speed);
	void SetAttackRange(int range);

	void SetIsCloseRange(bool closeRange);
	void SetBulletSize(int size);
	void SetBulletSpeed(float bulletSpeed);


	int GetAtkDamage();
	int GetAtkRange();
private:
	AnimatorComponent* m_idleAni = nullptr;
	AnimatorComponent* m_atkAni = nullptr;
	ColiderComponent* m_atkCol = nullptr;

	Monster* m_owner = nullptr;

	float					m_attackElapsed = 0.0f;
	float					m_attackSpeed = 1.4f;
	int						m_attackDamage = 0;
	int						m_attackRange = 10;

	POINT					m_bulletPos = {};
	float					m_bulletAngle = 0.0f;
	float					m_bulletSpeed = 100.0f;
	int						m_bulletSize = 0;

	bool					mb_isCloseRange = true;

};