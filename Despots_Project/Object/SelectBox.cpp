#include "SelectBox.h"
#include "Component/ImageComponent.h"
#include "Manager/GameManager.h"
#include "Util/Input.h"

void SelectBox::Init()
{
	m_img = new ImageComponent(this, 1);
	m_img->SetImage(L"Image/InterFace/SelectBox.png");
}

void SelectBox::Update()
{
	if (Input::GetButtonDown(VK_LBUTTON))
	{
		m_clickPos = Input::GetMousePosition();
		SetRect({ m_clickPos.x, m_clickPos.y, m_clickPos.x, m_clickPos.y });
	}
	else if (Input::GetButton(VK_LBUTTON))
	{
		POINT p = Input::GetMousePosition();
		RECT* temprc = GetRectP();
		if (p.x < temprc->right)
		{
			if (p.x > temprc->left)
				temprc->right -= (temprc->right - p.x);
			else			
				temprc->left = p.x;
		}
		if (p.x > temprc->left)
		{
			if (p.x < temprc->right)
				temprc->left += (p.x - temprc->left);
			else
				temprc->right = p.x;			
		}
		if (p.y < temprc->top)
		{
			temprc->top = p.y;
		}
		else
		{
			if(p.y < temprc->bottom)
				temprc->top = p.y;
			else
			{
				if (p.y < temprc->bottom)
					temprc->bottom = p.y;
			}
		}
		m_img->SetRect(*temprc);
	}

	if (GameManager::GetInstance()->GetGameState() == GameState::Battle)
	{
		m_img->SetIsVisible(false);
	}
	else
	{
		m_img->SetIsVisible(true);
	}

}
