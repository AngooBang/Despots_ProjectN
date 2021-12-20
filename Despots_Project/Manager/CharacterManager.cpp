#include "stdafx.h"
#include "CharacterManager.h"
#include "CameraManager.h"
#include "PathFinderManager.h"
#include "Object/Character.h"
#include "GameManager.h"
#include "Object/Tile.h"

void CharacterManager::Update()
{
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

	stack<pair<int, int>> path = PathFinderManager::GetInstance()->PathFind();

	//선택 캐릭터의 상태를 Move로 변화 및 path 지정
	selectedChar->SetPath(path);

}

void CharacterManager::SetScene(Scene* scene)
{
	_scene = scene;
}

void CharacterManager::SetLayer(Layer* layer)
{
	_layer = layer;
}


