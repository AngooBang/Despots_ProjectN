#include "TitleScene.h"

#include "Object/Text.h"
#include "Object/BackGround.h"

#include "Util/Input.h"

#include "Manager/SceneManager.h"

void TitleScene::Init()
{
	Layer* ui = FindLayer(L"UI");

	BackGround* tempBackGround = new BackGround(this, ui, L"BackGround");


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
