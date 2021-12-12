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
	Layer* back = FindLayer(L"Back");

	Layer* ob = FindLayer(L"Objects");

	BackGround* tempBackGround = new BackGround(this, back, L"BackGround");
	DespotLogo* despotLogo = new DespotLogo(this, back, L"DespotLogo");

	StartButton* startButton = new StartButton(this, ob, L"StartButton");
	ExitButton* exitButton = new ExitButton(this, ob, L"ExitButton");

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
