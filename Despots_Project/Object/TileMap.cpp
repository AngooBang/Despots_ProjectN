#include "stdafx.h"
#include "TileMap.h"
#include "Object/Tile.h"
#include "Component/ImageComponent.h"
#include "Manager/CameraManager.h"
#include "Object/Door.h"
#include "Object/FullMap.h"

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
	
	m_leftDoor = new Door(GetScene(), GetLayer(), L"LeftDoor" + m_roomNum, DoorDir::Left, this);
	m_leftDoor->SetPosition({ m_pos.x - 50, m_pos.y + 110 });
	m_leftDoor->Init();

	m_upDoor = new Door(GetScene(), GetLayer(), L"UpDoor" + m_roomNum, DoorDir::Top, this);
	m_upDoor->SetPosition({ m_pos.x + WALL_SIZE_X / 2 - 130, m_pos.y - 80 });
	m_upDoor->Init();

	m_rightDoor = new Door(GetScene(), GetLayer(), L"RightDoor" + m_roomNum, DoorDir::Right, this);
	m_rightDoor->SetPosition({ m_pos.x + WALL_SIZE_X - 10, m_pos.y + 110 });
	m_rightDoor->Init();

	m_downDoor = new Door(GetScene(), GetLayer(), L"DownDoor" + m_roomNum, DoorDir::Bottom, this);
	m_downDoor->SetPosition({ m_pos.x + WALL_SIZE_X / 2 - 130, m_pos.y + WALL_SIZE_Y + TILE_SIZE * TILE_SIZE_Y - 160 });
	m_downDoor->Init();
}

void TileMap::Update()
{
	MoveRoom();
	GameObject::Update();
}

void TileMap::MoveRoom()
{
	static int total = 0;
	int dir = -1;
	for (int i = 0; i < DoorDir::End; ++i)
	{
		if (mb_moveRoom[i])
			dir = i;
	}
	if (dir == -1) return;
	switch (dir)
	{
	case DoorDir::Left:
		if (total < ROOM_DISTANCE_X)
		{
			CameraManager::GetInstance()->AddCameraPos({ -10, 0 });
			total += 10;
		}
		else
		{
			total = 0;
			mb_moveRoom[dir] = false;
		}
		break;
	case DoorDir::Right:
		if (total < ROOM_DISTANCE_X)
		{
			CameraManager::GetInstance()->AddCameraPos({ 10, 0 });
			total += 10;
		}
		else
		{
			total = 0;
			mb_moveRoom[dir] = false;
		}
		break;
	case DoorDir::Top:
		if (total < ROOM_DISTANCE_Y)
		{
			CameraManager::GetInstance()->AddCameraPos({ 0, -10 });
			total += 10;
		}
		else
		{
			total = 0;
			mb_moveRoom[dir] = false;
		}
		break;
	case DoorDir::Bottom:
		if (total < ROOM_DISTANCE_Y)
		{
			CameraManager::GetInstance()->AddCameraPos({ 0, 10 });
			total += 10;
		}
		else
		{
			total = 0;
			mb_moveRoom[dir] = false;
		}
		break;
	default:
		break;

	}

}

void TileMap::SetMoveRoom(DoorDir dir)
{	
	mb_moveRoom[dir] = true;
}

void TileMap::SetRoomNum(int num)
{
	m_roomNum = num;
}

int TileMap::GetRoomNum()
{
	return m_roomNum;
}

void TileMap::Release()
{

}

void TileMap::InitTile()
{
	for (int i = 0; i < TILE_SIZE_Y; ++i)
	{
		for (int j = 0; j < TILE_SIZE_X; ++j)
		{
			m_tileInfo[i][j] = new Tile(GetScene(), GetLayer(), L"Tile" + m_roomNum + '_' + (i * TILE_SIZE_Y + j));
			m_tileInfo[i][j]->SetPosition({ m_pos.x + j * TILE_SIZE , m_pos.y + WALL_SIZE_Y + i * TILE_SIZE });

			m_tileInfo[i][j]->SetRect({ m_tileInfo[i][j]->GetPosition().x,
										m_tileInfo[i][j]->GetPosition().y,
										m_tileInfo[i][j]->GetPosition().x + TILE_SIZE,
										m_tileInfo[i][j]->GetPosition().y + TILE_SIZE });

			m_tileInfo[i][j]->SetImgComp(new ImageComponent(m_tileInfo[i][j], 2));
			m_tileInfo[i][j]->GetImgComp()->SetImage(L"Image/Map/Ground_0.bmp");
			m_tileInfo[i][j]->GetImgComp()->SetRect(m_tileInfo[i][j]->GetRect());

		}
	}

}

