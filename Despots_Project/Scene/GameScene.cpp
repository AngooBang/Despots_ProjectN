#include "GameScene.h"
#include "Object/BackGround.h"
#include "Object/TileMap.h"

void GameScene::Init()
{
	Layer* back = FindLayer(L"Back");
	Layer* ob = FindLayer(L"Objects");

	BackGround* tempBackGround = new BackGround(this, back, L"BackGround");

	TileMap* tileMap1 = new TileMap(this, ob, L"TileMap1");
	tileMap1->SetPosition({ 180, 70 });

	Scene::Init();
}

void GameScene::Update()
{
	Scene::Update();
}

void GameScene::PhysicsUpdate()
{
	Scene::PhysicsUpdate();
}

void GameScene::Render()
{
	Scene::Render();
}

void GameScene::Release()
{
	Scene::Release();
}
