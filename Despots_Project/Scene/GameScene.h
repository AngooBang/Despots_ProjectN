#pragma once
#include "Scene.h"

class Shop;
class UI;
class GameScene : public Scene
{
public:
	using Scene::Scene;

	virtual ~GameScene() noexcept = default;

	virtual void		Init() override;
	virtual void		Update() override;
	virtual void		PhysicsUpdate() override;
	virtual void		Render() override;
	virtual void		Release() override;

private:
	Layer* m_backLayer = nullptr;
	Layer* m_mapLayer = nullptr;
	Layer* m_objectLayer = nullptr;
	Layer* m_shopLayer = nullptr;
	Layer* m_uiLayer = nullptr;

	Shop* m_shop = nullptr;
	UI* m_ui = nullptr;

	bool mb_gameStart = false;
};