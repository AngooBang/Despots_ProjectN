#pragma once
#include "../Util/Singleton.h"
#include "IBehaviour.h"
#include "Object/Character.h"

enum class GameState { Stanby, Battle };

class TileMap;
class Tile;
class MoveFrame;
class Shop;
class GameManager : public Singleton<GameManager>, IBehaviour
{
public:


	virtual void Update() override;

	void CheckMonsterLeft();
	
	void AddStageNum(int num);

	POINT DistPosToTilePos(POINT pos);

	void CharacterMove(Tile* endTile);

	void BattleStart();

	void BattleQuit();

	void LoadStage();
	void ShopVisibleOff();

	Tile* GetNewCharTile();
	Tile* GetNewMonTile();
	TileMap* GetCurrTileMap();
	CharacterType GetCharType();
	GameState GetGameState();
	int GetStageNum();


	void SetCurrTileMap(TileMap* tileMap);
	void SetMoveFrame(MoveFrame* moveFrame);
	void SetCharType(CharacterType type);
	void SetShop(Shop* shop);

private:
	GameState m_gameState = GameState::Stanby;

	TileMap* m_currTileMap = nullptr;

	MoveFrame* m_moveFrame = nullptr;
	CharacterType m_charType = CharacterType::None;
	Shop* m_shop = nullptr;

	int m_stageNum = 1;
};