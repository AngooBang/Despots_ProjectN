#pragma once
#include "../Util/Singleton.h"

class TileMap;
class Tile;
class GameManager : public Singleton<GameManager>
{
public:


	Tile* GetNewCharTile();
	void SetCurrTileMap(TileMap* tileMap);

private:
	TileMap* m_currTileMap = nullptr;
};