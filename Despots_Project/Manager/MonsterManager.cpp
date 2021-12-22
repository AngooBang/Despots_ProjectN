#include "stdafx.h"
#include "MonsterManager.h"
#include "Manager/GameManager.h"
#include "Manager/PathFinderManager.h"
#include "Object/Tile.h"
#include "Object/Monster.h"

void MonsterManager::Update()
{
	for (int i = 0; i < m_addCount; ++i)
	{
		//Tile* tile = GameManager::GetInstance()->GetNewCharTile();
		//if (tile == nullptr)	return;

		//POINT charPos = { (tile->GetRect().left + tile->GetRect().right) / 2, (tile->GetRect().top + tile->GetRect().bottom) / 2 };


		//PathFinderManager::GetInstance()->SetInTileData(tile, 2);

		//Character* newChar = new Character(_scene, _layer, L"Character", charPos);
		//newChar->Init();
		//newChar->SetTilePos({ tile->x * 3 + 1, tile->y * 3 + 1 });


		//m_vecChar.push_back(newChar);

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


	//for (auto iter = m_vecMon.begin(); iter != m_vecMon.end(); ++iter)
	//{
	//	if ((*iter)->GetIsAlive() == false)
	//	{
	//		m_vecMon.erase(iter);
	//		SAFE_RELEASE((*iter));
	//	}
	//}

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
