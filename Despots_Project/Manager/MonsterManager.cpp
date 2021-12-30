#include "stdafx.h"
#include "MonsterManager.h"
#include "Manager/GameManager.h"
#include "Manager/PathFinderManager.h"
#include "Manager/CharacterManager.h"
#include "Object/Tile.h"
#include "Object/Monster.h"
#include "Object/Character.h"
#include "Util/Timer.h"
#include "Scene/Layer.h"

void MonsterManager::Update()
{
	//if (m_removeCount > 0)
	//{
	//	SAFE_RELEASE((*removeIter));
	//	m_vecMon.erase(removeIter);
	//}
	for (int i = 0; i < m_addCount; ++i)
	{
		Tile* tile = GameManager::GetInstance()->GetNewMonTile();
		if (tile == nullptr) return;

		POINT monPos = { (tile->GetRect().left + tile->GetRect().right) / 2, (tile->GetRect().top + tile->GetRect().bottom) / 2 };


		PathFinderManager::GetInstance()->SetInTileDataM(tile, 5);

		Monster* newMonster = new Monster(_scene, _layer, L"Monster", monPos);
		switch (GameManager::GetInstance()->GetStageNum())
		{
		case 1:
			newMonster->SetType(MonsterType::Dalek);
			break;
		case 2:
			newMonster->SetType(MonsterType::Necro);
			break;
		case 3:
			newMonster->SetType(MonsterType::Octopus);
			break;
		case 4:
			newMonster->SetType(MonsterType::Boss);
			break;
		}
		newMonster->Init();
		newMonster->SetTilePos({ tile->x * 3 + 1, tile->y * 3 + 1 });


		m_vecMon.push_back(newMonster);
	}
	m_addCount = 0;


	for (auto iter = m_vecMon.begin(); iter != m_vecMon.end();)
	{
		if ((*iter)->GetIsAlive() == false)
		{
			//removeIter = iter;
			//m_removeCount++;
			PathFinderManager::GetInstance()->SetInTileDataM((*iter)->GetTilePos().x, (*iter)->GetTilePos().y, 0);
			_layer->RemoveObject((*iter));
			SAFE_RELEASE((*iter));
			iter = m_vecMon.erase(iter);
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
		if (m_pathFindElapsed > 1.0f)
		{
			for (auto iter : m_vecMon)
			{
				if (iter->GetState() != MonsterState::Run)
					iter->SetState(MonsterState::Run);
			}
			m_pathFindElapsed = 0.0f;
			if (m_pfCount <= m_vecMon.size())
			{
				FindCharacterPath();
			}/*
			if (m_vecMonIter == m_vecMon.end())
			{
				m_vecMonIter = m_vecMon.begin();
				m_pfCount = 0;
			}*/
		}
		break;
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
	m_pfCount = 0;
	m_vecMonIter = m_vecMon.begin();
}

void MonsterManager::BattleQuit()
{
	// 게임오버 메시지 => 타이틀씬전환

}

void MonsterManager::FindCharacterPath()
{
	vector<Character*> vecChar = CharacterManager::GetInstance()->GetVecChar();
	while (m_vecMonIter != m_vecMon.end())
	{
		deque<POINT> tempDeq;

		POINT startPos = (*m_vecMonIter)->GetTilePos();
		for (auto chariter : vecChar)
		{
			POINT endPos = chariter->GetTilePos();
			deque<POINT> currDeq;

			PathFinderManager::GetInstance()->SetInTileDataM(startPos.x, startPos.y, 0);

			currDeq = PathFinderManager::GetInstance()->PathFindPoint(startPos, endPos);

			PathFinderManager::GetInstance()->SetInTileDataM(startPos.x, startPos.y, 5);
			if (currDeq.empty())
			{
				return;
			}
			if (tempDeq.size() > currDeq.size() || tempDeq.size() == 0)
			{
				tempDeq = currDeq;
				(*m_vecMonIter)->SetTarget(chariter);
			}
		}

		++m_pfCount;
		(*m_vecMonIter)->SetPath(tempDeq);
		(*m_vecMonIter)->SetState(MonsterState::Run);
		++m_vecMonIter;
		//if (m_pfCount % 5 == 0) break;
	}
}

void MonsterManager::FindNewPath(Monster* monster, bool sFloodFill, bool eFloodFill)
{
	vector<Character*> vecChar = CharacterManager::GetInstance()->GetVecChar();
	deque<POINT> tempDeq;

	POINT startPos = monster->GetTilePos();
	for (auto chariter : vecChar)
	{
		if (chariter->GetIsAlive() == false) continue;
		POINT endPos = chariter->GetTilePos();
		deque<POINT> currDeq;

		currDeq = PathFinderManager::GetInstance()->PathFindPoint(startPos, endPos, sFloodFill, eFloodFill);

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
