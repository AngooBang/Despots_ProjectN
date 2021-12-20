#pragma once
#include "GameObject.h"
class ImageComponent;
class Tile : public GameObject
{
public:
	using GameObject::GameObject;


	virtual void Render() override;

	void SetImgComp(ImageComponent* imgComp);
	ImageComponent* GetImgComp();

	int x;
	int y;

private:
	ImageComponent* m_img = nullptr;
};