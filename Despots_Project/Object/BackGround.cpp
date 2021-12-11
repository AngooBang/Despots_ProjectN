#include "BackGround.h"
#include "stdafx.h"
#include "Component/ImageComponent.h"
#include "Component/AnimatorComponent.h"

void BackGround::Init()
{
	ImageComponent* imgComp = new ImageComponent(this, 1);
	imgComp->SetImage(L"Image/Title/BackGround.bmp");
	imgComp->SetRect({ 0, 0, WIN_SIZE_X, WIN_SIZE_Y });

	ImageComponent* imgComp2 = new ImageComponent(this, 1);
	imgComp2->SetImage(L"Image/Title/Despot_Logo.bmp");
	imgComp2->SetRect({ (WIN_SIZE_X / 2) - 350, 50, (WIN_SIZE_X / 2) - 350 + 700, 50 + 400 });


}
