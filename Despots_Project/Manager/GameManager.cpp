#include "GameManager.h"
#include "stdafx.h"
#include "Util/Input.h"
#include "Manager/CharacterManager.h"
#include "Object/TileMap.h"
#include "Object/Tile.h"
#include "Object/MoveFrame.h"

void GameManager::Update()
{
	Tile* clickTile = nullptr;
	// 1. 타일에 클릭을 검사
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
				if (Input::GetButtonDown(VK_RBUTTON))
					CharacterManager::GetInstance()->GetMovePath(m_currTileMap->GetTileInfo()[y][x]);
			}
		}
	}
	// 2. 클릭된 타일을 가지고있는 캐릭터를 찾아 선택상태로 만들어줌
	CharacterManager::GetInstance()->SelectCharacter(clickTile);

	
}

Tile* GameManager::GetNewCharTile()
{
	for (int x = 1; x <= 7; ++x)
	{
		for (int y = 7; y >= 1; y--)
		{
			if (INTILE[y * 3 + 1][x * 3 + 1] == 0)
			{
				return m_currTileMap->GetTileInfo()[y][x];
			}
		}
	}

	return nullptr;
}

TileMap* GameManager::GetCurrTileMap()
{
	return m_currTileMap;
}

CharacterType GameManager::GetCharType()
{
	return m_charType;
}


void GameManager::CharacterMove(Tile* endTile)
{
}

void GameManager::SetCurrTileMap(TileMap* tileMap)
{
	m_currTileMap = tileMap;
}

void GameManager::SetMoveFrame(MoveFrame* moveFrame)
{
	m_moveFrame = moveFrame;
}

void GameManager::SetCharType(CharacterType type)
{
	m_charType = type;
}
