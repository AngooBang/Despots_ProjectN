#pragma once
#include "Util/Singleton.h"
#include "IBehaviour.h"
#include <vector>
#include <string>

class Monster;
class Scene;
class Layer;
class Tile;
class MonsterManager : public Singleton<MonsterManager>, IBehaviour
{
public:
	MonsterManager() noexcept = default;
	~MonsterManager() noexcept = default;

	virtual void Update() override;

	void AddMonster();

	void BattleStart();
	void BattleQuit();

	void FindCharacterPath();

	void FindNewPath(Monster* monster);

	void SetScene(Scene* scene);
	void SetLayer(Layer* layer);

	vector<Monster*> GetVecMon();

private:
	vector<Monster*> m_vecMon;
	vector<Monster*>::iterator removeIter;

	int	m_addCount = 0;
	int m_removeCount = 0;
	Scene* _scene = nullptr;
	Layer* _layer = nullptr;

};