#pragma once
#include "GameObject.h"

class ImageComponent;
class AnimatorComponent;
class Tile;
class Character : public GameObject
{
public:
	Character(Scene* scene, Layer* layer, const std::wstring& tag, POINT pos);

	virtual void Init() override;
	virtual void Update() override;

	void SetTile(Tile* tile);
	void SetIsSelected(bool isSelected);

	Tile* GetTile();
	bool GetIsSelected();


private:
	AnimatorComponent*	m_idleAni = nullptr;
	ImageComponent*		m_selectImg = nullptr;


	Tile*				m_seatTile = nullptr;

	bool				mb_isSelected = false;
};