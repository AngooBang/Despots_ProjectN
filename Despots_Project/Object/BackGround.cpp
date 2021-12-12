#include "BackGround.h"
#include "stdafx.h"
#include "Component/ImageComponent.h"
#include "Component/AnimatorComponent.h"

void BackGround::Init()
{
	ImageComponent* imgComp = new ImageComponent(this, 1);
	imgComp->SetImage(L"Image/Title/BackGround.bmp");
	imgComp->SetRect({ 0, 0, WIN_SIZE_X, WIN_SIZE_Y });


}
