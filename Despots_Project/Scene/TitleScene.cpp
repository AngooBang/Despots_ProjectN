#include "TitleScene.h"
#include "Manager/SceneManager.h"
#include "Util/Input.h"

#include "Object/Text.h"
#include "Object/BackGround.h"
#include "Object/DespotLogo.h"
#include "Object/StartButton.h"
#include "Object/ExitButton.h"



void TitleScene::Init()
{
	Layer* m_backLayer = FindLayer(L"Back");

	Layer* m_obLayer = FindLayer(L"Object");

	BackGround* tempBackGround = new BackGround(this, m_backLayer, L"BackGround");
	DespotLogo* despotLogo = new DespotLogo(this, m_backLayer, L"DespotLogo");

	StartButton* startButton = new StartButton(this, m_obLayer, L"StartButton");
	ExitButton* exitButton = new ExitButton(this, m_obLayer, L"ExitButton");

	//Text* tempTxt = new Text(this, ui, L"Temp Text");
	//tempTxt->SetPosition(500, 500);

	Scene::Init();
}

void TitleScene::Update()
{
	Scene::Update();

	if (Input::GetButtonDown(VK_SPACE))
	{
		SceneManager::GetInstance()->SetNextScene(L"Temp");
	}
}
