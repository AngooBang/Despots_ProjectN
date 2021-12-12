#pragma once
#include "GameObject.h"


#define TILE_SIZE_X 20
#define TILE_SIZE_Y 9
#define TILE_SIZE 45

#define WALL_SIZE_X 900
#define WALL_SIZE_Y 140

#define BOTTOM_SIZE_X 900
#define BOTTOM_SIZE_Y 50

class Door;
class ImageComponent;
struct Tile
{
	POINT pos = {};
	RECT shape = {};
	ImageComponent* img = nullptr;
	bool smallTile[3][3] = { false };
};

class TileMap : public GameObject
{
public:
	using GameObject::GameObject;

	virtual void Init() override;
	void InitTile();

	void MoveLeftRoom();

private:
	POINT m_pos = {};

	ImageComponent* m_wallImg = nullptr;
	ImageComponent* m_bottomImg = nullptr;

	Tile* m_tileInfo[TILE_SIZE_Y][TILE_SIZE_X] = { nullptr };

	Door* m_leftDoor = nullptr;
	Door* m_upDoor = nullptr;
	Door* m_rightDoor = nullptr;
	Door* m_downDoor = nullptr;
};