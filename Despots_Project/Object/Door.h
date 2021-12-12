#pragma once
#include "GameObject.h"

enum class DoorDir { Left, Top, Right, Bottom, End};


template <typename T>
class ButtonComponent;
class AnimatorComponent;
class TileMap;
class Door : public GameObject
{
public:
	using ButtonComponent = ButtonComponent<TileMap>;
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

private:
	DoorDir m_dir = DoorDir::End;
	POINT m_pos = {};
	RECT m_rect = {};

	TileMap* m_owner = nullptr;
	AnimatorComponent* m_doorAni = nullptr;
	ButtonComponent* m_button = nullptr;
};