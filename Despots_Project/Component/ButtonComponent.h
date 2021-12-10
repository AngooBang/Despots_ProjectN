#pragma once
#include "Component.h"
#include "stdafx.h"
template<typename GameObject>
class ButtonComponent : public Component
{
public:
	using func_t = GameObject;
	using callback_t = void(GameObject::*)();

public:
	enum class eButtonState { Idle, Hover, Click, None, };
	ButtonComponent(func_t* func, callback_t callback)
		: Component()
	{
		_func = func;
		_callback = callback;
	}
	using Component::Component;
	virtual ~ButtonComponent() noexcept = default;

	virtual void	Update() override
	{

		switch (state)
		{
		case eButtonState::Idle:
			if (PtInRect(&m_collisionRect, g_ptMouse))
				m_state = eButtonState::Hover;
			break;
		case eButtonState::Hover:
			if (INPUT_KEY_DOWN(VK_LBUTTON))
				m_state = eButtonState::Click;
			else if (false == PtInRect(&m_collisionRect, g_ptMouse))
				m_state = eButtonState::Idle;
			break;
		case eButtonState::Click:
			if (INPUT_KEY_UP(VK_LBUTTON))
			{
				if (PtInRect(&m_collisionRect, g_ptMouse))
				{
					//(*scene.*buttonFunction)();
					(_scene->*_callback)();
				}
				m_state = eButtonState::Idle;
			}
			break;
		case eButtonState::None:
			break;
		default:
			break;
		}
	}

	inline eButtonState GetButtonState() { return m_state; }

private:

	func_t* _func;
	callback_t _callback;

	eButtonState m_state = eButtonState::None;
	RECT m_collisionRect = {};
};

