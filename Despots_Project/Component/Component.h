#pragma once

#include "IBehaviour.h"
#include "Util/Type.h"

class GameObject;

class Component abstract : IBehaviour
{
public:
	Component(GameObject* owner, INT32 order = 100) noexcept;
	virtual ~Component() noexcept;

	INT32				GetOrder() const noexcept;

	virtual void		Init() override;
	virtual void		Update() override;
	virtual void		PhysicsUpdate() override;
	virtual void		Render() override;
	virtual void		Release() override;


	GameObject*			GetOwner();
	void				SetOwner(GameObject* owner);
	void				SetStopUpdate(bool stopUpdate);
	bool				GetStopUpdate();

protected:
	GameObject*			_owner = nullptr;

private:
	INT32				_order = 100;
	bool				_stopUpdate = false;
};