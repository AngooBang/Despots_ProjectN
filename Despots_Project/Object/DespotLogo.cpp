#include "DespotLogo.h"
#include "stdafx.h"
#include "../Component/ImageComponent.h"

void DespotLogo::Init()
{
	ImageComponent* imgComp2 = new ImageComponent(this, 1);
	imgComp2->SetImage(L"Image/Title/Despot_Logo.bmp");
	imgComp2->SetRect({ (WIN_SIZE_X / 2) - 350, 50, (WIN_SIZE_X / 2) - 350 + 700, 50 + 400 });

}
