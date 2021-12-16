#pragma once
#include "Util/Singleton.h"
#include "IBehaviour.h"
#include <vector>
#include <string>

class Character;
class Scene;
class Layer;
class Tile;
class CharacterManager : public Singleton<CharacterManager>, IBehaviour
{
public:
	CharacterManager() noexcept = default;
	~CharacterManager() noexcept = default;

	virtual void Update() override;

	void AddCharacter(Scene* scene, Layer* layer, const std::wstring& tag);

	void SelectCharacter(Tile* tile);

	void GetMovePath(Tile* endTile);

private:
	std::vector<Character*> m_vecChar;

};