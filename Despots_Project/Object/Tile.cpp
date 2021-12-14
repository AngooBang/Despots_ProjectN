#include "Tile.h"

void Tile::SetImgComp(ImageComponent* imgComp)
{
	m_img = imgComp;
}

ImageComponent* Tile::GetImgComp()
{
	return m_img;
}

