#include "FullMap.h"
#include "Object/TileMap.h"
#include "Manager/GameManager.h"

void FullMap::Init()
{
	m_tileMap1 = new TileMap(GetScene(), GetLayer(), L"TileMap1");
	m_tileMap1->SetPosition({ START_ROOM_X, START_ROOM_Y });
	m_tileMap1->SetRoomNum(1);
	m_tileMap1->Init();

	m_tileMap2 = new TileMap(GetScene(), GetLayer(), L"TileMap2");
	m_tileMap2->SetPosition({ START_ROOM_X + ROOM_DISTANCE_X, START_ROOM_Y });
	m_tileMap2->SetRoomNum(2);
	m_tileMap2->Init();
	
	m_tileMap3 = new TileMap(GetScene(), GetLayer(), L"TileMap3");
	m_tileMap3->SetPosition({ START_ROOM_X, START_ROOM_Y + ROOM_DISTANCE_Y });
	m_tileMap3->SetRoomNum(3);
	m_tileMap3->Init();

	m_tileMap4 = new TileMap(GetScene(), GetLayer(), L"TileMap4");
	m_tileMap4->SetPosition({ START_ROOM_X + ROOM_DISTANCE_X, START_ROOM_Y + ROOM_DISTANCE_Y });
	m_tileMap4->SetRoomNum(4);
	m_tileMap4->Init();

	GameManager::GetInstance()->SetCurrTileMap(m_tileMap1);
}

