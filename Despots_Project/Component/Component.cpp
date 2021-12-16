#include "stdafx.h"
#include "Object/GameObject.h"

#include "Component.h"

Component::Component(GameObject* owner, INT32 order) noexcept
	: _owner{ owner }, _order{ order }
{
	_owner->AddComponent(this);
}

Component::~Component() noexcept
{
	_owner->RemoveComponent(this);
	_owner = nullptr;
}

INT32 Component::GetOrder() const noexcept
{
	return _order;
}

void Component::Init()
{
}

void Component::Update()
{
}

void Component::PhysicsUpdate()
{
}

void Component::Render()
{
}

void Component::Release()
{
}

GameObject* Component::GetOwner()
{
	return _owner;
}

void Component::SetOwner(GameObject* owner)
{
	_owner = owner;
}

void Component::SetStopUpdate(bool stopUpdate)
{
	_stopUpdate = stopUpdate;
}

bool Component::GetStopUpdate()
{
	return _stopUpdate;
}
