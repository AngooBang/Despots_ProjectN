#include "GameManager.h"
#include "Util/Input.h"
#include "Manager/CharacterManager.h"
#include "Object/TileMap.h"
#include "Object/Tile.h"
#include "Object/MoveFrame.h"

void GameManager::Update()
{
	Tile* clickTile = nullptr;
	// 1. Ÿ�Ͽ� Ŭ���� �˻�
	for (int y = 1; y <= 7; ++y)
	{
		for (int x = 1; x <= 7; ++x)
		{
			RECT tempRc = m_currTileMap->GetTileInfo()[y][x]->GetRect();
			POINT mousePt = Input::GetMousePosition();
			
			if (PtInRect(&tempRc, mousePt))
			{
				m_moveFrame->SetRect(tempRc);
				if(Input::GetButtonDown(VK_LBUTTON))
					clickTile = m_currTileMap->GetTileInfo()[y][x];
			}
		}
	}
	// 2. Ŭ���� Ÿ���� �������ִ� ĳ���͸� ã�� ���û��·� �������
	CharacterManager::GetInstance()->SelectCharacter(clickTile);
	
}

Tile* GameManager::GetNewCharTile()
{
	for (int x = 1; x <= 7; ++x)
	{
		for (int y = 7; y >= 1; y--)
		{
			if (m_currTileMap->GetTileInfo()[y][x]->m_inTile[1][1] == false)
			{
				return m_currTileMap->GetTileInfo()[y][x];
			}
		}
	}

	return nullptr;
}

void GameManager::SetCurrTileMap(TileMap* tileMap)
{
	m_currTileMap = tileMap;
}

void GameManager::SetMoveFrame(MoveFrame* moveFrame)
{
	m_moveFrame = moveFrame;
}
