#include "ColiderManager.h"
#include "../Component/ColiderComponent.h"
#include "../Object/GameObject.h"
#include "Util/Input.h"
#include "stdafx.h"

void ColiderManager::AddColider(ColiderComponent* col)
{
	m_vecCols.push_back(col);
}

ColiderComponent* ColiderManager::FindColider(const wstring& tag)
{
	for (auto iter : m_vecCols)
	{
		if (iter->GetTag() == tag)
			return iter;
	}
	return nullptr;
}

void ColiderManager::CheckToMouse(ColiderComponent* col)
{	
	RECT tempRC = col->GetRect();
	if (PtInRect(&tempRC, Input::GetMousePosition()))
	{
		if (Input::GetButtonDown(VK_LBUTTON))
		{
			col->GetOwner()->OnColision(ColTypes::MouseClickDown);
			return;
		}
		if (Input::GetButtonUp(VK_LBUTTON))
		{
			col->GetOwner()->OnColision(ColTypes::MouseClickUp);
			return;
		}
		col->GetOwner()->OnColision(ColTypes::MouseHover);

	}
}

void ColiderManager::CheckToColider(ColiderComponent* col)
{
	RECT colRC = col->GetRect();

	RECT tempRC;
	
	for (auto iter : m_vecCols)
	{
		if (iter == col) continue;
		if (iter->GetIsAlive() == false) continue;
		RECT secRC = iter->GetRect();
		if (IntersectRect(&tempRC, &colRC, &secRC))
		{
			col->GetOwner()->OnColision(col, iter);
		}
	}
}

