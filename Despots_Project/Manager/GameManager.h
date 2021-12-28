#pragma once
#include "../Util/Singleton.h"
#include "IBehaviour.h"
#include "Object/Character.h"

enum class GameState { Stanby, Battle, EndBattle };

class TileMap;
class Tile;
class MoveFrame;
class Shop;
class UI;
class GameManager : public Singleton<GameManager>, IBehaviour
{
public:


	virtual void Update() override;

	void CheckTileSelect();

	void CheckMonsterLeft();
	void CheckCharacterLeft();
	
	void AddStageNum(int num);

	POINT DistPosToTilePos(POINT pos);

	void BattleStart();

	void BattleQuit();

	void GameOver();

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
	void SetUI(UI* ui);

private:
	GameState m_gameState = GameState::Stanby;

	TileMap* m_currTileMap = nullptr;

	MoveFrame* m_moveFrame = nullptr;
	CharacterType m_charType = CharacterType::None;
	Shop* m_shop = nullptr;
	UI* m_ui = nullptr;

	int m_stageNum = 1;
};