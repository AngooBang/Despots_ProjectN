#include "stdafx.h"
#include "MonsterManager.h"
#include "Manager/GameManager.h"
#include "Manager/PathFinderManager.h"
#include "Manager/CharacterManager.h"
#include "Object/Tile.h"
#include "Object/Monster.h"
#include "Object/Character.h"
#include "Scene/Layer.h"

void MonsterManager::Update()
{
	if (m_removeCount > 0)
	{
		SAFE_RELEASE((*removeIter));
		m_vecMon.erase(removeIter);
	}
	for (int i = 0; i < m_addCount; ++i)
	{
		Tile* tile = GameManager::GetInstance()->GetNewMonTile();
		if (tile == nullptr) return;

		POINT monPos = { (tile->GetRect().left + tile->GetRect().right) / 2, (tile->GetRect().top + tile->GetRect().bottom) / 2 };


		PathFinderManager::GetInstance()->SetInTileDataM(tile, 5);

		Monster* newMonster = new Monster(_scene, _layer, L"Monster", monPos);
		newMonster->Init();
		newMonster->SetTilePos({ tile->x * 3 + 1, tile->y * 3 + 1 });


		m_vecMon.push_back(newMonster);
	}
	m_addCount = 0;


	m_removeCount = 0;
	for (auto iter = m_vecMon.begin(); iter != m_vecMon.end(); ++iter)
	{
		if ((*iter)->GetIsAlive() == false)
		{
			removeIter = iter;
			m_removeCount++;
			//SAFE_RELEASE((*iter));
			//m_vecMon.erase(iter);
		}
	}

}

void MonsterManager::AddMonster()
{
	++m_addCount;
}

void MonsterManager::BattleStart()
{
	for (auto iter : m_vecMon)
	{
		iter->SetState(MonsterState::Idle);
	}
	//최초 길찾기 실행.
	FindCharacterPath();
}

void MonsterManager::BattleQuit()
{
	// 게임오버 메시지 => 타이틀씬전환
}

void MonsterManager::FindCharacterPath()
{
	vector<Character*> vecChar = CharacterManager::GetInstance()->GetVecChar();
	for (auto iter : m_vecMon)
	{
		deque<POINT> tempDeq;

		POINT startPos = iter->GetTilePos();
		for (auto chariter : vecChar)
		{
			POINT endPos = chariter->GetTilePos();
			deque<POINT> currDeq;

			PathFinderManager::GetInstance()->SetInTileDataM(startPos.x, startPos.y, 0);

			PathFinderManager::GetInstance()->ClearMap();
			PathFinderManager::GetInstance()->PrintMap();
			currDeq = PathFinderManager::GetInstance()->PathFindPoint(startPos, endPos);

			PathFinderManager::GetInstance()->SetInTileDataM(startPos.x, startPos.y, 5);
			if (currDeq.empty())
			{
				return;
			}
			if (tempDeq.size() > currDeq.size() || tempDeq.size() == 0)
			{
				tempDeq = currDeq;
				iter->SetTarget(chariter);
			}
		}
		iter->SetPath(tempDeq);
	}
}

void MonsterManager::FindNewPath(Monster* monster)
{
	vector<Character*> vecChar = CharacterManager::GetInstance()->GetVecChar();
	deque<POINT> tempDeq;

	POINT startPos = monster->GetTilePos();
	for (auto chariter : vecChar)
	{
		if (chariter->GetIsAlive() == false) continue;
		POINT endPos = chariter->GetTilePos();
		deque<POINT> currDeq;

		currDeq = PathFinderManager::GetInstance()->PathFindPoint(startPos, endPos);

		if (currDeq.empty())
		{
			return;
		}

		if (tempDeq.size() > currDeq.size() || tempDeq.size() == 0)
		{
			tempDeq = currDeq;
			monster->SetTarget(chariter);
		}

	}

	monster->SetPath(tempDeq);
}

void MonsterManager::SetScene(Scene* scene)
{
	_scene = scene;
}

void MonsterManager::SetLayer(Layer* layer)
{
	_layer = layer;
}

vector<Monster*> MonsterManager::GetVecMon()
{
	return m_vecMon;
}
