#pragma once
#include "Util/Singleton.h"
#include <vector>
#include <string>

class Character;
class Scene;
class Layer;
class CharacterManager : public Singleton<CharacterManager>
{
public:
	CharacterManager() noexcept = default;
	~CharacterManager() noexcept = default;

	void AddCharacter(Scene* scene, Layer* layer, const std::wstring& tag);
private:
	std::vector<Character*> m_vecChar;
};