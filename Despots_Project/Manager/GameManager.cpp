#include "GameManager.h"
#include "stdafx.h"
#include "Util/Input.h"
#include "Manager/CharacterManager.h"
#include "Manager/MonsterManager.h"
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

Tile* GameManager::GetNewMonTile()
{
	//가득 차있는지 체크
	bool isFull = true;
	for (int i = 12; i <= 18; ++i)
	{
		for (int j = 1; j <= 7; ++j)
		{
			if (INTILE[j * 3 + 1][i * 3 + 1] == 0)
			{
				isFull = false;
			}
		}
	}
	if (isFull)
		return nullptr;
	else
	{
		while (true)
		{
			int x = rand() % 7 + 1;
			int y = rand() % 7 + 1;

			if (INTILE[(y * 3 + 1)][x * 3 + 1 + 33] == 0)
			{
				return m_currTileMap->GetTileInfo()[y][x + 11];
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

GameState GameManager::GetGameState()
{
	return m_gameState;
}


void GameManager::CharacterMove(Tile* endTile)
{
}

void GameManager::BattleStart()
{
	m_gameState = GameState::Battle;
	MonsterManager::GetInstance()->BattleStart();
	CharacterManager::GetInstance()->BattleStart();
}

void GameManager::LoadStage()
{
	switch (m_stageNum)
	{
	case 1:
		for (int i = 0; i < 1; ++i)
		{
			MonsterManager::GetInstance()->AddMonster();
		}
		break;
	case 2:
		for (int i = 0; i < 2; ++i)
		{
			MonsterManager::GetInstance()->AddMonster();
		}
		break;
	case 3:
		for (int i = 0; i < 3; ++i)
		{
			MonsterManager::GetInstance()->AddMonster();
		}
		break;
	case 4:
		for (int i = 0; i < 1; ++i)
		{
			MonsterManager::GetInstance()->AddMonster();
		}
		break;
	}
	CharacterManager::GetInstance()->FlyCharacter();
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

void GameManager::AddStageNum(int num)
{
	m_stageNum += num;
}

POINT GameManager::DistPosToTilePos(POINT pos)
{
	POINT valuePos = pos;
	POINT tileStartPos = m_currTileMap->GetTileInfo()[0][0]->GetPosition();

	valuePos.x -= tileStartPos.x;
	valuePos.y -= tileStartPos.y;

	valuePos.x /= 15;
	valuePos.y /= 15;

	return valuePos;
}

int GameManager::GetStageNum()
{
	return m_stageNum;
}
