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

	void BattleStart();

	void FindMonsterPath();

	void FindNewPath(Character* character);

	void FlyCharacter();
	void VisibleOff();

	void AddCharacter();

	void SelectCharacter(Tile* tile);

	void GetMovePath(Tile* endTile);

	void SetScene(Scene* scene);
	void SetLayer(Layer* layer);

private:
	std::vector<Character*> m_vecChar;
	int	m_addCount = 0;

	float	m_pathFindElapsed = 0.0f;
	Scene* _scene = nullptr;
	Layer* _layer = nullptr;

};