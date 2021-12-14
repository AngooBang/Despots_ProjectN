#pragma once
#include "GameObject.h"
class ImageComponent;
class Tile : public GameObject
{
public:
	using GameObject::GameObject;



	void SetImgComp(ImageComponent* imgComp);
	ImageComponent* GetImgComp();

	bool m_inTile[3][3] = { false };
private:
	ImageComponent* m_img = nullptr;
};