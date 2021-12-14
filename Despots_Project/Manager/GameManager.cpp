#include "GameManager.h"
#include "Object/TileMap.h"
#include "Object/Tile.h"

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
