#include "CharacterAttack.h"
#include "Object/Character.h"
#include "Component/AnimatorComponent.h"
#include "Util/Timer.h"

CharacterAttack::CharacterAttack(Character* owner, INT32 order) noexcept
	:Component(owner, order)
{
	m_owner = owner;
}

void CharacterAttack::Init()
{
	m_attackElapsed = 0.0f;
	m_attackSpeed = 1400.0f;
	m_attackDamage = 10;
}

void CharacterAttack::Update()
{
	if (m_owner->GetState() != CharacterState::Attack) return;

	// ÄÄÆ÷³ÍÆ®È­
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
		m_attackElapsed += Timer::GetDeltaTime();
	}
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

int CharacterAttack::GetAtkDamage()
{
	return m_attackDamage;
}
