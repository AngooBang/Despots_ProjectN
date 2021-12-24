#include "stdafx.h"
#include "Manager/CharacterManager.h"
#include "Manager/CameraManager.h"
#include "Manager/PathFinderManager.h"
#include "Manager/MonsterManager.h"
#include "Manager/GameManager.h"
#include "Object/Character.h"
#include "Object/Monster.h"
#include "Object/Tile.h"
#include "Util/Timer.h"

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

	m_pathFindElapsed += Timer::GetDeltaTime();
	switch (GameManager::GetInstance()->GetGameState())
	{
	case GameState::Stanby:

		break;
	case GameState::Battle:
		if (m_pathFindElapsed > 1.0f)
		{
			for (auto iter : m_vecChar)
			{
				if(iter->GetState() != CharacterState::Run)
					iter->SetState(CharacterState::Run);
			}
			m_pathFindElapsed = 0.0f;
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

	// 최초 길찾기 실행.
	FindMonsterPath();
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
	for(auto iter : m_vecChar)
	{
		deque<POINT> tempDeq;

		POINT startPos = iter->GetTilePos();
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
				iter->SetTarget(moniter);
			}
			//	}
			//}

		}
		iter->SetPath(tempDeq);
		iter->SetState(CharacterState::Run);
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


