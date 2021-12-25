#include "stdafx.h"
#include "CharacterAttack.h"
#include "Object/Character.h"
#include "Object/Monster.h"
#include "Component/AnimatorComponent.h"
#include "Manager/CharacterManager.h"
#include "Util/Timer.h"

CharacterAttack::CharacterAttack(Character* owner, INT32 order) noexcept
	:Component(owner, order)
{
	m_owner = owner;
}

void CharacterAttack::Update()
{
	if (m_owner->GetState() == CharacterState::Attack)
	{
		// 애니메이션 처리
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
			//공격애니가 끝나고 타겟이 죽었다면 새로운 타겟 과 경로 지정
			if (m_owner->GetTarget() != nullptr)
			{
				if (m_owner->GetTarget()->GetState() == MonsterState::Dead)
					CharacterManager::GetInstance()->FindNewPath(m_owner, true, true);
			}
			else
				m_owner->SetState(CharacterState::Idle);
			m_attackElapsed += Timer::GetDeltaTime();
		}
	}


	if (mb_isCloseRange)
	{
		POINT ownerPos = m_owner->GetPosition();
		int ownerWidth = m_owner->GetRect().right - m_owner->GetRect().left;
		int ownerHeight = m_owner->GetRect().bottom - m_owner->GetRect().top;
		switch (m_owner->GetDir())
		{
		case CharacterDir::Left:
			m_atkCol->SetRect({ ownerPos.x - ((ownerWidth / 2) + m_attackRange),
				ownerPos.y - ((ownerHeight / 2) + m_attackRange),
				ownerPos.x,
				ownerPos.y + (ownerHeight / 2) + m_attackRange });
			break;
		case CharacterDir::Right:
			m_atkCol->SetRect({ ownerPos.x ,
				ownerPos.y - ((ownerHeight)+m_attackRange),
				ownerPos.x + ((ownerWidth / 2) + m_attackRange),
				ownerPos.y + (ownerHeight / 2) + m_attackRange });
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
}

void CharacterAttack::SetShotData()
{
	if (m_owner->GetTarget() == nullptr) return;
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

void CharacterAttack::ShotColider()
{
	if (m_owner->GetTarget() == nullptr) return;
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

void CharacterAttack::SetIdleAni(AnimatorComponent* idleAni)
{
	m_idleAni = idleAni;
}

void CharacterAttack::SetAtkAni(AnimatorComponent* atkAni)
{
	m_atkAni = atkAni;
}

void CharacterAttack::SetAtkCol(ColiderComponent* col)
{
	m_atkCol = col;
}

void CharacterAttack::SetAttackDamage(int damage)
{
	m_attackDamage = damage;
}

void CharacterAttack::SetAttackSpeed(float speed)
{
	m_attackSpeed = speed;
}

void CharacterAttack::SetAttackRange(int range)
{
	m_attackRange = range;
}

void CharacterAttack::SetIsCloseRange(bool closeRange)
{
	mb_isCloseRange = closeRange;
}

void CharacterAttack::SetBulletSize(int size)
{
	m_bulletSize = size;
}

void CharacterAttack::SetBulletSpeed(float bulletSpeed)
{
	m_bulletSpeed = bulletSpeed;
}

int CharacterAttack::GetAtkDamage()
{
	return m_attackDamage;
}

int CharacterAttack::GetAtkRange()
{
	return m_attackRange;
}
