#include "ColiderComponent.h"
#include "stdafx.h"
#include "Manager/ImageManagerD2.h"
#include "Manager/ColiderManager.h"

ColiderComponent::ColiderComponent(GameObject* owner, INT32 order, RECT rect, ColTypes type, const wstring& tag)
	:Component(owner, order)
{
	ColiderManager::GetInstance()->AddColider(this);
	m_colRect = rect;
	m_type = type;
	m_tag = tag;
}

void ColiderComponent::Update()
{
	// �ʿ��� ������ �ڱ��ڽ��� �־��ָ� �ݶ��̴��Ŵ������� �浹���� Ȯ�� ��û

	ColiderManager::GetInstance()->CheckToMouse(this);
}

void ColiderComponent::Render()
{
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

void ColiderComponent::SetRect(RECT rect)
{
	m_colRect = rect;
}

RECT ColiderComponent::GetRect()
{
	return m_colRect;
}

GameObject* ColiderComponent::GetOwner()
{
	return _owner;
}
