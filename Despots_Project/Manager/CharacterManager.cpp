#include "CharacterManager.h"
#include "Object/Character.h"
#include "GameManager.h"
#include "Object/Tile.h"

void CharacterManager::AddCharacter(Scene* scene, Layer* layer, const std::wstring& tag)
{
	Tile* tile = GameManager::GetInstance()->GetNewCharTile();
	if (tile == nullptr)	return;
	
	Character* newChar = new Character(scene, layer, tag, tile->GetPosition());

									tile->m_inTile[0][1] = true;
	tile->m_inTile[1][0] = true;	tile->m_inTile[1][1] = true;	tile->m_inTile[1][2] = true;
									tile->m_inTile[2][1] = true;

	newChar->Init();
	m_vecChar.push_back(newChar);
}
