#pragma once
#include "Component.h"
#include "stdafx.h"
#include "Util/Input.h"
#include "Object/GameObject.h"
enum class eButtonState { Idle, Hover, Click, None, };

template<typename GameObject>
class ButtonComponent : public Component
{
public:
	using gameobj_t = GameObject;
	using callback_t = void(GameObject::*)();

public:


	ButtonComponent(GameObject* owner, INT32 order, gameobj_t* btn, callback_t callback)
		: Component(owner, order)
	{
		_btn = btn;
		_callback = callback;
	}
	virtual ~ButtonComponent() noexcept = default;

	virtual void	Update() override
	{
		switch (m_state)
		{
		case eButtonState::Idle:
			if (PtInRect(&m_collisionRect, Input::GetMousePosition()))
			{
				m_state = eButtonState::Hover;
				mb_changeState = true;
			}
			break;
		case eButtonState::Hover:
			if (INPUT_KEY_DOWN(VK_LBUTTON))
			{
				m_state = eButtonState::Click;
				mb_changeState = true;
			}
			else if (false == PtInRect(&m_collisionRect, Input::GetMousePosition()))
			{
				m_state = eButtonState::Idle;
				mb_changeState = true;
			}
			break;
		case eButtonState::Click:
			if (INPUT_KEY_UP(VK_LBUTTON))
			{
				if (PtInRect(&m_collisionRect, Input::GetMousePosition()))
				{
					//(*scene.*buttonFunction)();
					(_btn->*_callback)();
				}
				else
				{
					m_state = eButtonState::Idle;
					mb_changeState = true;
				}
			}
			break;
		case eButtonState::None:
			break;
		default:
			break;
		}
	}

	inline void SetButtonState(eButtonState state) { m_state = state; }

	inline eButtonState GetButtonState() { return m_state; }
	inline void SetCollisionRect(RECT rect) { m_collisionRect = rect; }


	inline void SetChangeState(bool changeState) { mb_changeState = changeState; }
	inline bool GetChangeState() { return mb_changeState; }

private:
	gameobj_t* _btn;
	callback_t _callback;

	eButtonState m_state = eButtonState::Idle;
	RECT m_collisionRect = {};

	bool mb_changeState = false;
};

