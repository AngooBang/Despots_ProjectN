#include "stdafx.h"
#include "TileMap.h"
#include "Component/ImageComponent.h"
#include "Object/Door.h"

void TileMap::Init()
{
	m_pos = GetPosition();
	m_wallImg = new ImageComponent(this, 1);
	m_wallImg->SetImage(L"Image/Map/Wall.bmp");
	m_wallImg->SetRect({ m_pos.x, m_pos.y, m_pos.x + WALL_SIZE_X, m_pos.y + WALL_SIZE_Y });

	InitTile();

	m_bottomImg = new ImageComponent(this, 1);
	m_bottomImg->SetImage(L"Image/Map/Bottom.bmp");
	m_bottomImg->SetRect({ m_pos.x,
		m_pos.y + WALL_SIZE_Y + (TILE_SIZE * TILE_SIZE_Y),
		m_pos.x + BOTTOM_SIZE_X,
		m_pos.y + WALL_SIZE_Y + (TILE_SIZE * TILE_SIZE_Y) + BOTTOM_SIZE_Y });
	
	m_leftDoor = new Door(GetScene(), GetLayer(), L"LeftDoor", DoorDir::Left, this);
	m_leftDoor->SetPosition({ m_pos.x - 50, m_pos.y + 110 });
	m_leftDoor->Init();

	m_upDoor = new Door(GetScene(), GetLayer(), L"UpDoor", DoorDir::Top, this);
	m_upDoor->SetPosition({ m_pos.x + WALL_SIZE_X / 2 - 130, m_pos.y - 80 });
	m_upDoor->Init();

	m_rightDoor = new Door(GetScene(), GetLayer(), L"RightDoor", DoorDir::Right, this);
	m_rightDoor->SetPosition({ m_pos.x + WALL_SIZE_X - 10, m_pos.y + 110 });
	m_rightDoor->Init();

	m_downDoor = new Door(GetScene(), GetLayer(), L"DownDoor", DoorDir::Bottom, this);
	m_downDoor->SetPosition({ m_pos.x + WALL_SIZE_X / 2 - 130, m_pos.y + WALL_SIZE_Y + TILE_SIZE * TILE_SIZE_Y - 160 });
	m_downDoor->Init();
}

void TileMap::MoveLeftRoom()
{
}

void TileMap::InitTile()
{
	for (int i = 0; i < TILE_SIZE_Y; ++i)
	{
		for (int j = 0; j < TILE_SIZE_X; ++j)
		{
			m_tileInfo[i][j] = new Tile;
			m_tileInfo[i][j]->pos.x = m_pos.x + j * TILE_SIZE;
			m_tileInfo[i][j]->pos.y = m_pos.y + WALL_SIZE_Y + i * TILE_SIZE;

			m_tileInfo[i][j]->shape.left = m_tileInfo[i][j]->pos.x;
			m_tileInfo[i][j]->shape.top = m_tileInfo[i][j]->pos.y;
			m_tileInfo[i][j]->shape.right = m_tileInfo[i][j]->pos.x + TILE_SIZE;
			m_tileInfo[i][j]->shape.bottom = m_tileInfo[i][j]->pos.y + TILE_SIZE;

			m_tileInfo[i][j]->img = new ImageComponent(this, 2);
			m_tileInfo[i][j]->img->SetImage(L"Image/Map/Ground_0.bmp");
			m_tileInfo[i][j]->img->SetRect({ m_tileInfo[i][j]->shape.left, m_tileInfo[i][j]->shape.top, m_tileInfo[i][j]->shape.right, m_tileInfo[i][j]->shape.bottom});						

		}
	}

}

