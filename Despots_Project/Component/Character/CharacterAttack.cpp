#include "CharacterAttack.h"
#include "Object/Character.h"
#include "Component/AnimatorComponent.h"
#include "Util/Timer.h"

CharacterAttack::CharacterAttack(Character* owner, INT32 order) noexcept
	:Component(owner, order)
{
	m_owner = owner;
}

void CharacterAttack::Update()
{
	if (m_owner->GetState() != CharacterState::Attack) return;

	if (mb_isCloseRange)
	{
		POINT ownerPos = m_owner->GetPosition();
		int ownerWidth = m_owner->GetRect().right - m_owner->GetRect().left;
		int ownerHeight = m_owner->GetRect().bottom - m_owner->GetRect().top;
		switch (m_owner->GetDir())
		{
		case CharacterDir::Left:
			m_atkCol->SetRect({ ownerPos.x - (ownerWidth / 2) + m_attackRange, ownerPos.y - (ownerHeight / 2), ownerPos.x,  ownerPos.y + (ownerHeight / 2) });
			break;
		case CharacterDir::Right:
			m_atkCol->SetRect({ ownerPos.x , ownerPos.y - (ownerHeight / 2), ownerPos.x + (ownerWidth / 2) + m_attackRange,  ownerPos.y + (ownerHeight / 2) });
			break;
		default:
			break;
		}
	}
	else
	{
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
		m_atkCol->SetIsAlive(false);
		m_owner->SetState(CharacterState::Idle);
		m_attackElapsed += Timer::GetDeltaTime();
	}
}

void CharacterAttack::ShotColider()
{
	POINT ownerPos = m_owner->GetPosition();
	m_atkCol->SetRect({ ownerPos.x - m_bulletSize / 2, ownerPos.y - m_bulletSize / 2, ownerPos.x + m_bulletSize / 2, ownerPos.y + m_bulletSize / 2 });

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

int CharacterAttack::GetAtkDamage()
{
	return m_attackDamage;
}

int CharacterAttack::GetAtkRange()
{
	return m_attackRange;
}
