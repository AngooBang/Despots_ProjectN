#include "ColiderComponent.h"
#include "stdafx.h"
#include "Manager/ImageManagerD2.h"
#include "Manager/ColiderManager.h"
#include "Component/ImageComponent.h"

ColiderComponent::ColiderComponent(GameObject* owner, INT32 order, RECT rect, ColTypes type, const wstring& tag)
	:Component(owner, order)
{
	ColiderManager::GetInstance()->AddColider(this);
	m_colRect = rect;
	m_type = type;
	m_tag = tag;
}

void ColiderComponent::Init()
{
	m_img = new ImageComponent(_owner, 2);
	m_img->SetIsCam(false);
}

void ColiderComponent::Update()
{
	// 필요할 때마다 자기자신을 넣어주며 콜라이더매니저에게 충돌여부 확인 요청
	if (!mb_isAlive)
	{
		return;
	}

	ColiderManager::GetInstance()->CheckToMouse(this);
	ColiderManager::GetInstance()->CheckToColider(this);
	m_img->SetRect(m_colRect);
}

void ColiderComponent::Render()
{
	if (!mb_isAlive) return;
	ID2D1SolidColorBrush* brush;
	ImageManagerD2::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkGray), &brush);
	
	D2D1_RECT_F rect = { (FLOAT)m_colRect.left, (FLOAT)m_colRect.top, (FLOAT)m_colRect.right, (FLOAT)m_colRect.bottom };
	
	ImageManagerD2::GetInstance()->GetRenderTarget()->DrawRectangle(rect, brush);
}

ColTypes ColiderComponent::GetType()
{
	return m_type;
}

wstring ColiderComponent::GetTag()
{
	return m_tag;
}

void ColiderComponent::SetImgVisible(bool imgVisible)
{
	m_img->SetIsVisible(imgVisible);
}

void ColiderComponent::SetImage(const wchar_t* path)
{
	m_img->SetImage(path);
}

void ColiderComponent::SetIsAlive(bool isAlive)
{
	mb_isAlive = isAlive;
}

void ColiderComponent::SetRect(RECT rect)
{
	m_colRect = rect;
}

void ColiderComponent::SetCAtkComp(CharacterAttack* cAtkComp)
{
	m_cAtkComp = cAtkComp;
}

void ColiderComponent::SetMAtkComp(MonsterAttack* mAtkComp)
{
	m_mAtkComp = mAtkComp;
}

RECT ColiderComponent::GetRect()
{
	return m_colRect;
}

CharacterAttack* ColiderComponent::GetCAtkComp()
{
	return m_cAtkComp;
}

bool ColiderComponent::GetIsAlive()
{
	return mb_isAlive;
}

GameObject* ColiderComponent::GetOwner()
{
	return _owner;
}
