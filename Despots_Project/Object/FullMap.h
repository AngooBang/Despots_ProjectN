#pragma once
#include "GameObject.h"

#define ROOM_DISTANCE_X 1140
#define ROOM_DISTANCE_Y 700

#define START_ROOM_X 180
#define START_ROOM_Y 70

class TileMap;
class FullMap : public GameObject
{
public:
	using GameObject::GameObject;

	virtual void Init() override;

private:
	TileMap* m_tileMap1 = nullptr;
	TileMap* m_tileMap2 = nullptr;
	TileMap* m_tileMap3 = nullptr;
	TileMap* m_tileMap4 = nullptr;

};