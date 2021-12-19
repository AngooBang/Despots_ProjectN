#pragma once
#include "../Util/Singleton.h"
#include "IBehaviour.h"
#include "Object/Character.h"

enum class GameState { Stanby, Battle };

class TileMap;
class Tile;
class MoveFrame;
class GameManager : public Singleton<GameManager>, IBehaviour
{
public:


	virtual void Update() override;

	Tile* GetNewCharTile();
	Tile* GetNewMonTile();
	TileMap* GetCurrTileMap();
	CharacterType GetCharType();

	void SetCurrTileMap(TileMap* tileMap);
	void SetMoveFrame(MoveFrame* moveFrame);
	void SetCharType(CharacterType type);

	void CharacterMove(Tile* endTile);

	void BattleStart();

private:
	GameState m_gameState = GameState::Stanby;

	TileMap* m_currTileMap = nullptr;

	MoveFrame* m_moveFrame = nullptr;
	CharacterType m_charType = CharacterType::None;

};