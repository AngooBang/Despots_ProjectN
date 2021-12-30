#include "stdafx.h"
#include "Manager/CharacterManager.h"
#include "Manager/CameraManager.h"
#include "Manager/PathFinderManager.h"
#include "Manager/MonsterManager.h"
#include "Manager/GameManager.h"
#include "Object/Character.h"
#include "Object/Monster.h"
#include "Object/TileMap.h"
#include "Object/Tile.h"
#include "Util/Timer.h"
#include "Scene/Layer.h"

void CharacterManager::Update()
{
	// addCharacter가 실행된만큼 Update에서 처리 (Update주기 차이때문)
	for (int i = 0; i < m_addCount; ++i)
	{
		Tile* tile = GameManager::GetInstance()->GetNewCharTile();
		if (tile == nullptr)	return;

		POINT charPos = { (tile->GetRect().left + tile->GetRect().right) / 2,
			(tile->GetRect().top + tile->GetRect().bottom) / 2 };


		PathFinderManager::GetInstance()->SetInTileData(tile, 2);

		Character* newChar = new Character(_scene, _layer, L"Character", charPos);
		newChar->Init();
		newChar->SetTilePos({ tile->x * 3 + 1, tile->y * 3 + 1 });

		m_vecChar.push_back(newChar);
	}
	m_addCount = 0;

	for (auto iter = m_vecChar.begin(); iter != m_vecChar.end();)
	{
		if ((*iter)->GetIsAlive() == false)
		{
			//removeIter = iter;
			//m_removeCount++;
			PathFinderManager::GetInstance()->SetInTileData((*iter)->GetTilePos().x, (*iter)->GetTilePos().y, 0);
			_layer->RemoveObject((*iter));
			SAFE_RELEASE((*iter));
			iter = m_vecChar.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	m_pathFindElapsed += Timer::GetDeltaTime();
	switch (GameManager::GetInstance()->GetGameState())
	{
	case GameState::Stanby:

		break;
	case GameState::Battle:
		if (m_pathFindElapsed > 0.5f)
		{
			for (auto iter : m_vecChar)
			{
				if(iter->GetState() != CharacterState::Run)
					iter->SetState(CharacterState::Run);
			}
			m_pathFindElapsed = 0.0f;
			if (m_pfCount <= m_vecChar.size())
			{
				FindMonsterPath();
			}/*
			if (m_vecCharIter == m_vecChar.end())
			{
				m_vecCharIter = m_vecChar.begin();
				m_pfCount = 0;
			}*/
		}
		break;
	}
}

void CharacterManager::BattleStart()
{
	// 배틀 시작시 있던 위치 기억시킴
	for (auto iter : m_vecChar)
	{
		iter->SetStanbyPos(iter->GetTilePos());
	}
	m_pfCount = 0;
	m_vecCharIter = m_vecChar.begin();
}

void CharacterManager::BattleQuit()
{
	for (auto iter : m_vecChar)
	{

		POINT startPos = iter->GetTilePos();
		POINT endPos = iter->GetStanbyPos();

		iter->SetPath(PathFinderManager::GetInstance()->PathFindPoint(startPos, endPos, true, true));
		iter->SetState(CharacterState::Run);
		iter->SetTarget(nullptr);
	}
}


void CharacterManager::FindMonsterPath()
{
	// 캐릭터를 하나하나 작업해서 path를 넣어줌(가장 가까운 몬스터 기준으로..)
	vector<Monster*> vecMon = MonsterManager::GetInstance()->GetVecMon();
	while(m_vecCharIter != m_vecChar.end())
	{
		deque<POINT> tempDeq;

		POINT startPos = (*m_vecCharIter)->GetTilePos();
		for (auto moniter : vecMon)
		{
			POINT endPos = moniter->GetTilePos();



			deque<POINT> currDeq;
			//if (abs(startPos.x - endPos.x) > 2)
			//{
			//	if (abs(startPos.y - endPos.y) > 2)
			//	{
			currDeq = PathFinderManager::GetInstance()->PathFindPoint(startPos, endPos);
			if (currDeq.empty())
			{
				return;
			}

			if (tempDeq.size() > currDeq.size() || tempDeq.size() == 0)
			{
				tempDeq = currDeq;
				(*m_vecCharIter)->SetTarget(moniter);
			}

		}
		++m_pfCount;
		(*m_vecCharIter)->SetPath(tempDeq);
		(*m_vecCharIter)->SetState(CharacterState::Run);
		++m_vecCharIter;
		//if (m_pfCount % 5 == 0) break;
	}
}

void CharacterManager::FindNewPath(Character* character, bool sFloodFill , bool eFloodFill)
{
	vector<Monster*> vecMon = MonsterManager::GetInstance()->GetVecMon();
	deque<POINT> tempDeq;

	POINT startPos = character->GetTilePos();
	for (auto moniter : vecMon)
	{
		if (moniter->GetIsAlive() == false) continue;
		if (moniter->GetState() == MonsterState::Dead) continue;
		POINT endPos = moniter->GetTilePos();



		deque<POINT> currDeq;
		currDeq = PathFinderManager::GetInstance()->PathFindPoint(startPos, endPos, sFloodFill, eFloodFill);

		if (tempDeq.size() > currDeq.size() || tempDeq.size() == 0)
		{
			tempDeq = currDeq;
			character->SetTarget(moniter);
		}
	}

	character->SetPath(tempDeq);
	character->SetState(CharacterState::Run);
}

void CharacterManager::FlyCharacter()
{
	// 타일맵을 받아서 m_tilePos의 값으로 포지션값을 맞춰준다.

	// 상태를 Fly로 만들어 위에서 떨어지게끔 만들어준다.
	for (auto iter : m_vecChar)
	{
		iter->SetState(CharacterState::Fly);
	}
}

void CharacterManager::VisibleOff()
{
	for (auto iter : m_vecChar)
	{
		iter->SetState(CharacterState::End);
	}
}

void CharacterManager::AddCharacter()
{
	++m_addCount;
}

void CharacterManager::AddDefaultChar()
{
	for (int i = 1; i <= 4; ++i)
	{
		Tile* tile = nullptr;
		switch (i)
		{
		case 1:
			tile = GameManager::GetInstance()->GetCurrTileMap()->GetTileInfo()[4][7];
			break;
		case 2:
			tile = GameManager::GetInstance()->GetCurrTileMap()->GetTileInfo()[5][6];
			break;
		case 3:
			tile = GameManager::GetInstance()->GetCurrTileMap()->GetTileInfo()[3][1];
			break;
		case 4:
			tile = GameManager::GetInstance()->GetCurrTileMap()->GetTileInfo()[6][1];
			break;
		}
		POINT charPos = { (tile->GetRect().left + tile->GetRect().right) / 2,
			(tile->GetRect().top + tile->GetRect().bottom) / 2 };


		PathFinderManager::GetInstance()->SetInTileData(tile, 2);
		Character* newChar = new Character(_scene, _layer, L"Character", charPos);
		newChar->Init();
		newChar->SetTilePos({ tile->x * 3 + 1, tile->y * 3 + 1 });

		switch (i)
		{
		case 1:
			newChar->SetType(CharacterType::Shield);
			break;
		case 2:
			newChar->SetType(CharacterType::GutSword);
			break;
		case 3:
			newChar->SetType(CharacterType::Crossbow);
			break;
		case 4:
			newChar->SetType(CharacterType::Normal);
			break;
		}
		newChar->SetIsClassChanged(true);
		m_vecChar.push_back(newChar);
	}
	FlyCharacter();
}

void CharacterManager::SelectCharacter(Tile* tile)
{
	if (tile == nullptr)	return;

	for (auto iter : m_vecChar)
	{
		iter->SetIsSelected(false);
	}

	for (auto iter : m_vecChar)
	{
		if ((iter->GetTilePos().x - 1) / 3 == tile->x && (iter->GetTilePos().y - 1) / 3 == tile->y)
		{
			iter->SetIsSelected(true);
		}
	}
}

void CharacterManager::GetMovePath(Tile* endTile)
{
	// 일단은 캐릭터가 있는곳이면 이동불가능
	if (INTILE[endTile->y * 3 + 1][endTile->x * 3 + 1] == 2) return;
	Character* selectedChar = nullptr;

	for (auto iter : m_vecChar)
	{
		if (iter->GetIsSelected() == true)
			selectedChar = iter;
	}
	// 선택된 캐릭터가 없으면 이동불가능
	if (selectedChar == nullptr) return;

	POINT tilePos = selectedChar->GetTilePos();

	PathFinderManager::GetInstance()->SetInTileData(tilePos.x, tilePos.y, 0);

	INTILE[tilePos.y][tilePos.x] = 1;
	//Tile* scTile = nullptr;
	//scTile = selectedChar->GetTile();

	//SetInTileData(scTile, 0);
	//INTILE[scTile->y * 3 + 1][scTile->x * 3 + 1] = 1;

	INTILE[endTile->y * 3 + 1][endTile->x * 3 + 1] = 3;

	deque<POINT> path = PathFinderManager::GetInstance()->PathFind();

	//선택 캐릭터의 상태를 Move로 변화 및 path 지정
	selectedChar->SetPath(path);
	selectedChar->SetState(CharacterState::Run);

}

void CharacterManager::SetScene(Scene* scene)
{
	_scene = scene;
}

void CharacterManager::SetLayer(Layer* layer)
{
	_layer = layer;
}

vector<Character*> CharacterManager::GetVecChar()
{
	return m_vecChar;
}


