#include "HpBar.h"
#include "Component/ImageComponent.h"

void HpBar::Init()
{
	m_emptyImg = new ImageComponent(this, 1);
	m_emptyImg->SetImage(L"Image/Character/HpBar_Empty.png");
	m_emptyImg->SetIsCam(false);

	m_fillImg = new ImageComponent(this, 1);
	m_fillImg->SetIsCam(false);

	
}

void HpBar::Update()
{
	POINT ownerPos = m_owner->GetPosition();
	int ownerHeight = m_owner->GetRect().bottom - m_owner->GetRect().top;

	SetRect({ ownerPos.x - HPBAR_WIDTH / 2,
		ownerPos.y - (ownerHeight / 2) - 10 - HPBAR_HEIGHT,
		ownerPos.x + HPBAR_WIDTH / 2,
		ownerPos.y - (ownerHeight / 2) - 10 });

	m_emptyImg->SetRect(GetRect());

	float hpWidth = (float)m_nowHp / (float)m_maxHp;
	if (hpWidth > 1.0f)
	{
		hpWidth = 1.0f;
	}
	m_fillImg->SetRect({ GetRect().left, GetRect().top, GetRect().left + (INT)((FLOAT)HPBAR_WIDTH * hpWidth), GetRect().bottom });
}


void HpBar::SetFillImg(const wchar_t* path)
{
	m_fillImg->SetImage(path);
}

void HpBar::SetOwner(GameObject* owner)
{
	m_owner = owner;
}

void HpBar::SetMaxHp(int max)
{
	m_maxHp = max;
}

void HpBar::SetNowHp(int now)
{
	m_nowHp = now;
}