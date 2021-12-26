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
	void BattleQuit();

	void AddCharacter();

	void AddDefaultChar();

	void FindMonsterPath();

	void FindNewPath(Character* character, bool sFloodFill = false, bool eFloodFill = true);

	void FlyCharacter();
	void VisibleOff();


	void SelectCharacter(Tile* tile);

	void GetMovePath(Tile* endTile);


	void SetScene(Scene* scene);
	void SetLayer(Layer* layer);

	vector<Character*> GetVecChar();

private:
	vector<Character*> m_vecChar;
	vector<Character*>::iterator m_vecCharIter;
	int	m_addCount = 0;
	int m_pfCount = 0;
	float	m_pathFindElapsed = 0.0f;
	Scene* _scene = nullptr;
	Layer* _layer = nullptr;

};