#include "BackGround.h"
#include "../stdafx.h"
#include "../Component/ImageComponent.h"
#include "Component/AnimatorComponent.h"

void BackGround::Init()
{
	ImageComponent* imgComp = new ImageComponent(this, 1);
	imgComp->SetImage(L"Image/Title/BackGround.bmp");
	imgComp->SetRect({ 0, 0, WIN_SIZE_X, WIN_SIZE_Y });

	AnimatorComponent* aniComp = new AnimatorComponent(this, 2);
	aniComp->SetImage(L"Image/Map/Left_Door.png");
	aniComp->SetRect({ 100, 100, 180, 430 });
	aniComp->SetFrame(4, 1);
	aniComp->SetIsLoop(true);
	aniComp->SetMotionSpeed(80.0f);
}
