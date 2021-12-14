#include "CameraManager.h"

void CameraManager::AddCameraPos(POINT pos)
{
	m_cameraPos.x += pos.x;
	m_cameraPos.y += pos.y;
}

void CameraManager::SetCameraPos(POINT pos)
{
	m_cameraPos = pos;
}

POINT CameraManager::GetCameraPos()
{
	return m_cameraPos;
}
