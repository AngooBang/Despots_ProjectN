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

	void SetScene(Scene* scene);
	void SetLayer(Layer* layer);

private:
	std::vector<Monster*> m_vecMon;

	int	m_addCount = 0;

	Scene* _scene = nullptr;
	Layer* _layer = nullptr;

};