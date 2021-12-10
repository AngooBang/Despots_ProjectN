#include "TitleScene.h"
#include "Manager/SceneManager.h"
#include "Util/Input.h"

#include "Object/Text.h"
#include "Object/BackGround.h"
#include "Object/StartButton.h"



void TitleScene::Init()
{
	Layer* ui = FindLayer(L"UI");

	Layer* ob = FindLayer(L"Objects");

	BackGround* tempBackGround = new BackGround(this, ui, L"BackGround");

	StartButton* startButton = new StartButton(this, ob, L"StartButton");

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
