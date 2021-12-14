#pragma once
#include "Scene.h"

class GameScene final : public Scene
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
	Layer* m_obLayer = nullptr;
};