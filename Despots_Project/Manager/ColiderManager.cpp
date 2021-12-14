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
	RECT tempRC = col->GetShape();
	if (PtInRect(&tempRC, Input::GetMousePosition()))
	{
		if (Input::GetButtonDown(VK_LBUTTON))
		{
			col->GetOwner()->OnColision(ColTypes::MouseClick);
			return;
		}

		col->GetOwner()->OnColision(ColTypes::MouseHover);

	}
}

