#pragma once

#include <Windows.h>

struct IBehaviour
{
	virtual ~IBehaviour() { };

	virtual void		Init() { }
	virtual void		Update() { }
	virtual void		PhysicsUpdate() { }
	virtual void		Render() { }
	virtual void		Release() { }
};