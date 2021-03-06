#include "GameScene.h"
#include "Object/BackGround.h"
#include "Object/FullMap.h"
#include "Object/SelectBox.h"
#include "Object/MoveFrame.h"
#include "Object/FightButton.h"
#include "Object/Shop.h"
#include "Object/UI.h"
#include "Util/Input.h"
#include "Scene/Layer.h"
#include "Manager/CameraManager.h"
#include "Manager/GameManager.h"
#include "Manager/CharacterManager.h"
#include "Manager/MonsterManager.h"
#include "Manager/PathFinderManager.h"

void GameScene::Init()
{
	m_backLayer = FindLayer(L"Back");
	m_mapLayer = FindLayer(L"Map");
	m_objectLayer = FindLayer(L"Object");
	m_shopLayer = FindLayer(L"Shop");
	m_uiLayer = FindLayer(L"UI");

	BackGround* backGround = new BackGround(this, m_backLayer, L"BackGround");


	FullMap* fullMap = new FullMap(this, m_mapLayer, L"FullMap");

	//shop->Init();

	MoveFrame* moveFrame = new MoveFrame(this, m_objectLayer, L"MoveFrame");
	m_shop = new Shop(this, m_shopLayer, L"Shop");

	//SelectBox* selectBox = new SelectBox(this, m_uiLayer, L"SelectBox");

	FightButton* fightBtn = new FightButton(this, m_uiLayer, L"FightButton");
	m_ui = new UI(this, m_uiLayer, L"UI");
	m_ui->Init();

	CharacterManager::GetInstance()->SetScene(this);
	CharacterManager::GetInstance()->SetLayer(m_objectLayer);

	MonsterManager::GetInstance()->SetScene(this);
	MonsterManager::GetInstance()->SetLayer(m_objectLayer);

	GameManager::GetInstance()->SetUI(m_ui);
	GameManager::GetInstance()->SetShop(m_shop);
	GameManager::GetInstance()->LoadStage();
	Scene::Init();

	mb_gameStart = false;
}

void GameScene::Update()
{
	MonsterManager::GetInstance()->Update();
	CharacterManager::GetInstance()->Update();
	GameManager::GetInstance()->Update();
	Scene::Update();

	if (Input::GetButton(VK_LEFT))
		CameraManager::GetInstance()->AddCameraPos({ -10, 0 });
	if (Input::GetButton(VK_RIGHT))
		CameraManager::GetInstance()->AddCameraPos({ 10, 0 });
	if (Input::GetButton(VK_UP))
		CameraManager::GetInstance()->AddCameraPos({ 0, -10 });
	if (Input::GetButton(VK_DOWN))
		CameraManager::GetInstance()->AddCameraPos({ 0, 10 });

	if (Input::GetButtonDown('C'))
		CharacterManager::GetInstance()->AddCharacter();

	if (Input::GetButtonDown('M'))
		MonsterManager::GetInstance()->AddMonster();

	if (Input::GetButtonDown('S'))
	{
		m_shop->Show();
	}

	if (Input::GetButtonDown('P'))
		PathFinderManager::GetInstance()->PrintMap();



	if (mb_gameStart == false)
	{
		CharacterManager::GetInstance()->AddDefaultChar();
		mb_gameStart = true;
	}

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
