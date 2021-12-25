#pragma once
#include "GameObject.h"
class ImageComponent;
class UI : public GameObject
{
public:
	using GameObject::GameObject;

	virtual void Init() override;

	void SetMinimapImg(const wchar_t* path);

private:
	ImageComponent* m_uiImg = nullptr;
	ImageComponent* m_minimapImg = nullptr;
};