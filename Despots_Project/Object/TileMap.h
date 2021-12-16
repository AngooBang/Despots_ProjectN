#pragma once
#include "GameObject.h"
#include "Object/Door.h"

#define TILE_SIZE_X 20
#define TILE_SIZE_Y 9
#define TILE_SIZE 45

#define WALL_SIZE_X 900
#define WALL_SIZE_Y 140

#define BOTTOM_SIZE_X 900
#define BOTTOM_SIZE_Y 50

class Tile;
class ImageComponent;
class TileMap : public GameObject
{
public:
	using GameObject::GameObject;

	virtual void Init() override;
	virtual void Update() override;

	virtual void Render() override;
	virtual void Release() override;
	void InitTile();

	void MoveRoom();

	void SetMoveRoom(DoorDir dir);

	void SetRoomNum(int num);

	int GetRoomNum();

	inline auto GetTileInfo() { return m_tileInfo; }
private:
	POINT m_pos = {};

	ImageComponent* m_wallImg = nullptr;
	ImageComponent* m_bottomImg = nullptr;

	Tile* m_tileInfo[TILE_SIZE_Y][TILE_SIZE_X] = { nullptr };

	Door* m_leftDoor = nullptr;
	Door* m_upDoor = nullptr;
	Door* m_rightDoor = nullptr;
	Door* m_downDoor = nullptr;

	bool mb_moveRoom[DoorDir::End] = { false };
	int m_roomNum = -1;
};