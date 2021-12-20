#pragma once
#include "GameObject.h"

enum DoorDir { Left, Top, Right, Bottom, End};

#define LDOOR_COL_RECT { 140, 300, 180, 520 }
#define TDOOR_COL_RECT { 550, 40, 710, 200 }
#define RDOOR_COL_RECT { 1080, 300, 1120, 520 }
#define BDOOR_COL_RECT { 550, 505, 710, 665 }

enum class DoorState { Idle, Hover, Click };

class AnimatorComponent;
class TileMap;
class Door : public GameObject
{
public:
	//GameObject(Scene* scene, Layer* layer, const std::wstring& tag);
	Door(Scene* scene, Layer* layer, const std::wstring& tag, DoorDir dir, TileMap* owner)
		: GameObject(scene, layer, tag)
	{
		m_dir = dir;
		m_owner = owner;
	}
	virtual ~Door() noexcept = default;

	virtual void Init() override;
	virtual void Update() override;
	virtual void OnColision(ColTypes tag) override;
	virtual void Render() override;

	void SetIsVisible(bool isVisible);


private:
	DoorDir m_dir = DoorDir::End;
	POINT m_pos = {};
	RECT m_rect = {};
	RECT m_collisionRect = {};

	TileMap* m_owner = nullptr;
	AnimatorComponent* m_doorAni = nullptr;

	DoorState m_state = DoorState::Idle;

	ColiderComponent* m_colider = nullptr;

	bool mb_chageState = false;
	bool mb_isVisible = true;
};