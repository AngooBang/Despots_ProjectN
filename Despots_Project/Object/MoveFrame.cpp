#include "MoveFrame.h"
#include "Component/ImageComponent.h"
#include "Manager/GameManager.h"

void MoveFrame::Init()
{
	m_img = new ImageComponent(this, 1);
	m_img->SetImage(L"Image/Map/MoveFrame.png");
	m_img->SetRect({ 0, 0, 45, 45 });
	GameManager::GetInstance()->SetMoveFrame(this);
}

void MoveFrame::Update()
{
	if (GetRect().left > 0)
	{
		m_img->SetRect(GetRect());
	}
}

void MoveFrame::Render()
{
	GameObject::Render();
}


