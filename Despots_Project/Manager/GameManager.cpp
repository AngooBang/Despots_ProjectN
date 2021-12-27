#include "GameManager.h"
#include "stdafx.h"
#include "Util/Input.h"
#include "Manager/CharacterManager.h"
#include "Manager/MonsterManager.h"
#include "Manager/SceneManager.h"
#include "Object/TileMap.h"
#include "Object/Tile.h"
#include "Object/MoveFrame.h"
#include "Object/Monster.h"
#include "Object/Shop.h"
#include "Object/UI.h"

void GameManager::Update()
{
	if (m_gameState == GameState::Stanby)
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
					if (Input::GetButtonDown(VK_LBUTTON))
						clickTile = m_currTileMap->GetTileInfo()[y][x];
					if (Input::GetButtonDown(VK_RBUTTON))
						CharacterManager::GetInstance()->GetMovePath(m_currTileMap->GetTileInfo()[y][x]);
				}
			}
		}
		// 2. Ŭ���� Ÿ���� �������ִ� ĳ���͸� ã�� ���û��·� �������
		CharacterManager::GetInstance()->SelectCharacter(clickTile);
	}

	// ���������϶� �������� Ȯ�� �� ���ٸ� �ٽ� ���Ĺ��̷�~
	if (m_gameState == GameState::Battle)
	{
		CheckMonsterLeft();
		CheckCharacterLeft();
	}
}

void GameManager::CheckMonsterLeft()
{
	vector<Monster*> tempMon = MonsterManager::GetInstance()->GetVecMon();

	bool isMonsterLeft = false;
	for (auto iter : tempMon)
	{
		if (iter->GetIsAlive())
			isMonsterLeft = true;
	}

	if (!isMonsterLeft)
	{
		BattleQuit();
		// ĳ���Ͱ� ����� GameOver�� ���� Ÿ��Ʋ������ ���ư��¸�� �ʿ�
	}
	return;
}

void GameManager::CheckCharacterLeft()
{
	vector<Character*> tempChar = CharacterManager::GetInstance()->GetVecChar();

	bool isCharacterLeft = false;
	for (auto iter : tempChar)
	{
		if (iter->GetIsAlive())
			isCharacterLeft = true;
	}

	if (!isCharacterLeft)
	{
		GameOver();
		// ĳ���Ͱ� ����� GameOver�� ���� Ÿ��Ʋ������ ���ư��¸�� �ʿ�
	}
	return;
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
	//���� ���ִ��� üũ
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

void GameManager::BattleStart()
{
	m_gameState = GameState::Battle;
	MonsterManager::GetInstance()->BattleStart();
	CharacterManager::GetInstance()->BattleStart();
	m_shop->SetIsAlive(false);
}

void GameManager::BattleQuit()
{
	// ������ ������ ���Ĺ��̷� �Ѿ�� �Լ� ���� �ʿ� (ĳ��������ġ�� ������ ��ġ�� �̵�, ���¸� Idle��, ������ �����, ������ �߰��� ��..)
	m_gameState = GameState::EndBattle;
	CharacterManager::GetInstance()->BattleQuit();
	m_shop->Show();
}

void GameManager::GameOver()
{
	m_gameState = GameState::Stanby;
	SceneManager::GetInstance()->SetNextScene(L"Title");
	SceneManager::GetInstance()->ChangeScene();
}

void GameManager::LoadStage()
{
	// ���� ���� �ٸ����������� �̵��� ��������
	switch (m_stageNum)
	{
	case 1:
		for (int i = 0; i < 1; ++i)
		{
			MonsterManager::GetInstance()->AddMonster();
		}
		m_ui->SetMinimapImg(L"Image/UI/mini_01.png");
		break;
	case 2:
		for (int i = 0; i < 2; ++i)
		{
			MonsterManager::GetInstance()->AddMonster();
		}
		m_ui->SetMinimapImg(L"Image/UI/mini_02.png");
		break;
	case 3:
		for (int i = 0; i < 3; ++i)
		{
			MonsterManager::GetInstance()->AddMonster();
		}
		m_ui->SetMinimapImg(L"Image/UI/mini_03.png");
		break;
	case 4:
		for (int i = 0; i < 1; ++i)
		{
			MonsterManager::GetInstance()->AddMonster();
		}
		m_ui->SetMinimapImg(L"Image/UI/mini_04.png");
		break;
	}
	m_gameState = GameState::Stanby;
	// ĳ���� �̵�(fly �ִϸ��̼� ���)
	CharacterManager::GetInstance()->FlyCharacter();
}

void GameManager::ShopVisibleOff()
{
	// ����������
	m_shop->SetIsAlive(false);
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

void GameManager::SetShop(Shop* shop)
{
	m_shop = shop;
}

void GameManager::SetUI(UI* ui)
{
	m_ui = ui;
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
