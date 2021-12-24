#include "MonsterAttack.h"
#include "stdafx.h"
#include "Object/Character.h"
#include "Object/Monster.h"
#include "Component/AnimatorComponent.h"
#include "Util/Timer.h"

MonsterAttack::MonsterAttack(Monster* owner, INT32 order) noexcept
	:Component(owner, order)
{
	m_owner = owner;
}

void MonsterAttack::Update()
{
	if (m_owner->GetState() != MonsterState::Attack) return;

	if (mb_isCloseRange)
	{
		POINT ownerPos = m_owner->GetPosition();
		int ownerWidth = m_owner->GetRect().right - m_owner->GetRect().left;
		int ownerHeight = m_owner->GetRect().bottom - m_owner->GetRect().top;
		switch (m_owner->GetDir())
		{
		case MonsterDir::Left:
			m_atkCol->SetRect({ ownerPos.x - (ownerWidth / 2) + m_attackRange, ownerPos.y - (ownerHeight / 2), ownerPos.x,  ownerPos.y + (ownerHeight / 2) });
			break;
		case MonsterDir::Right:
			m_atkCol->SetRect({ ownerPos.x , ownerPos.y - (ownerHeight / 2), ownerPos.x + (ownerWidth / 2) + m_attackRange,  ownerPos.y + (ownerHeight / 2) });
			break;
		default:
			break;
		}
	}
	else
	{
		if (m_atkCol->GetIsAlive() == false)
			SetShotData();
		else
			ShotColider();
	}

	// 局聪皋捞记 贸府
	if (m_attackElapsed > m_attackSpeed)
	{
		m_atkAni->SetCurrFrame(0);
		m_atkAni->SetEndAni(false);

		m_idleAni->SetIsVisible(false);
		m_atkAni->SetIsVisible(true);
		m_atkCol->SetIsAlive(true);
		m_attackElapsed = 0.0f;
	}

	if (m_atkAni->GetEndAni())
	{
		m_idleAni->SetIsVisible(true);
		m_atkAni->SetIsVisible(false);
		if (mb_isCloseRange)
			m_atkCol->SetIsAlive(false);
		m_owner->SetState(MonsterState::Idle);
		m_attackElapsed += Timer::GetDeltaTime();
	}
}

void MonsterAttack::SetShotData()
{
	m_atkCol->SetImgVisible(false);

	POINT ownerPos = m_owner->GetPosition();
	POINT targetPos = m_owner->GetTarget()->GetPosition();
	m_bulletPos = ownerPos;

	m_atkCol->SetRect({ m_bulletPos.x - m_bulletSize / 2,
		m_bulletPos.y - m_bulletSize / 2,
		m_bulletPos.x + m_bulletSize / 2,
		m_bulletPos.y + m_bulletSize / 2 });

	m_bulletAngle = atan2f(
		-(targetPos.y - ownerPos.y),
		targetPos.x - ownerPos.x);
}

void MonsterAttack::ShotColider()
{
	m_atkCol->SetImgVisible(true);

	m_bulletPos.x += cos(m_bulletAngle) * m_bulletSpeed * Timer::GetDeltaTime();
	m_bulletPos.y -= sin(m_bulletAngle) * m_bulletSpeed * Timer::GetDeltaTime();

	m_atkCol->SetRect({ m_bulletPos.x - m_bulletSize / 2,
		m_bulletPos.y - m_bulletSize / 2,
		m_bulletPos.x + m_bulletSize / 2,
		m_bulletPos.y + m_bulletSize / 2 });

	if (m_bulletPos.x >= WIN_SIZE_X || m_bulletPos.x <= 0 || m_bulletPos.y >= WIN_SIZE_Y || m_bulletPos.y <= 0)
		m_atkCol->SetIsAlive(false);
}

void MonsterAttack::SetIdleAni(AnimatorComponent* idleAni)
{
	m_idleAni = idleAni;
}

void MonsterAttack::SetAtkAni(AnimatorComponent* atkAni)
{
	m_atkAni = atkAni;
}

void MonsterAttack::SetAtkCol(ColiderComponent* col)
{
	m_atkCol = col;
}

void MonsterAttack::SetAttackDamage(int damage)
{
	m_attackDamage = damage;
}

void MonsterAttack::SetAttackSpeed(float speed)
{
	m_attackSpeed = speed;
}

void MonsterAttack::SetAttackRange(int range)
{
	m_attackRange = range;
}

void MonsterAttack::SetIsCloseRange(bool closeRange)
{
	mb_isCloseRange = closeRange;
}

void MonsterAttack::SetBulletSize(int size)
{
	m_bulletSize = size;
}

void MonsterAttack::SetBulletSpeed(float bulletSpeed)
{
	m_bulletSpeed = bulletSpeed;
}

int MonsterAttack::GetAtkDamage()
{
	return m_attackDamage;
}

int MonsterAttack::GetAtkRange()
{
	return m_attackRange;
}
