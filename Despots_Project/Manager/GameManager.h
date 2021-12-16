#pragma once
#include "../Util/Singleton.h"
#include "IBehaviour.h"

class TileMap;
class Tile;
class MoveFrame;
class GameManager : public Singleton<GameManager>, IBehaviour
{
public:


	virtual void Update() override;

	Tile* GetNewCharTile();
	TileMap* GetCurrTileMap();

	void SetCurrTileMap(TileMap* tileMap);
	void SetMoveFrame(MoveFrame* moveFrame);
	void CharacterMove(Tile* endTile);

private:
	TileMap* m_currTileMap = nullptr;

	MoveFrame* m_moveFrame = nullptr;
};