#include "GameScene.h"
#include "Object/BackGround.h"
#include "Object/FullMap.h"
#include "../Util/Input.h"
#include "../Manager/CameraManager.h"
#include "../Manager/GameManager.h"
#include "../Manager/CharacterManager.h"

void GameScene::Init()
{
	m_backLayer = FindLayer(L"Back");
	m_obLayer = FindLayer(L"Objects");

	BackGround* backGround = new BackGround(this, m_backLayer, L"BackGround");

	FullMap* fullMap = new FullMap(this, m_obLayer, L"FullMap");

	Scene::Init();
}

void GameScene::Update()
{
	if (Input::GetButton(VK_LEFT))
		CameraManager::GetInstance()->AddCameraPos({ -10, 0 });
	if (Input::GetButton(VK_RIGHT))
		CameraManager::GetInstance()->AddCameraPos({ 10, 0 });
	if (Input::GetButton(VK_UP))
		CameraManager::GetInstance()->AddCameraPos({ 0, -10 });
	if (Input::GetButton(VK_DOWN))
		CameraManager::GetInstance()->AddCameraPos({ 0, 10 });

	if (Input::GetButtonDown('C'))
		CharacterManager::GetInstance()->AddCharacter(this, m_obLayer, L"Character");

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
