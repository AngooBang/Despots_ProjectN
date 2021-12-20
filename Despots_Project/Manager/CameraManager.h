#pragma once
#include <Windows.h>
#include "Util/Singleton.h"

class Scene;

class CameraManager : public Singleton<CameraManager>
{
public:
	CameraManager() noexcept = default;
	~CameraManager() noexcept = default;

	void AddCameraPos(POINT pos);
	void SetCameraPos(POINT pos);
	POINT GetCameraPos();
private:
	POINT m_cameraPos = {0, 0};
};