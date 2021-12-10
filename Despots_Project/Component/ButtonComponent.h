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

	// 이거 그냥 Component생성자도 따로 쓰는 경우가 있어서 2개만든거죠? 소리 안들려요...
	// 지금 생성자가 두개인가요? 제가 주석처리해서 지금은 1개예요 원래 2개였어요
	// 아아 지워도 될것같아요 이거떄문인가요? 일단 더 봐야해요
//	using Component::Component;
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
				m_state = eButtonState::Hover;
			break;
		case eButtonState::Hover:
			if (INPUT_KEY_DOWN(VK_LBUTTON))
				m_state = eButtonState::Click;
			else if (false == PtInRect(&m_collisionRect, Input::GetMousePosition()))
				m_state = eButtonState::Idle;
			break;
		case eButtonState::Click:
			if (INPUT_KEY_UP(VK_LBUTTON))
			{
				if (PtInRect(&m_collisionRect, Input::GetMousePosition()))
				{
					//(*scene.*buttonFunction)();
					(_btn->*_callback)();
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
	inline void SetCollisionRect(RECT rect) { m_collisionRect = rect; }

private:
	gameobj_t* _btn;
	callback_t _callback;

	eButtonState m_state = eButtonState::Idle;
	RECT m_collisionRect = {};
};

