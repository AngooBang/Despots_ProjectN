#pragma once

#include <Windows.h>
#include <vector>
#include <string>

#include "Util/Type.h"
#include "IBehaviour.h"
#include "Component/ColiderComponent.h"

class Scene;
class Layer;
class Component;
class GameObject abstract : IBehaviour
{
public:
	GameObject(Scene* scene, Layer* layer, const std::wstring& tag);
	virtual ~GameObject() noexcept;

	virtual void	Init() override;
	virtual void	Update() override;
	virtual void	PhysicsUpdate() override;
	virtual void	OnColision(ColTypes tag) { };
	virtual void	OnColision(ColiderComponent* col1, ColiderComponent* col2) { };
	virtual void	Render() override;
	virtual void	Release() override;

	void						AddComponent(Component* component);
	void						RemoveComponent(Component* component);
	std::vector<Component*>&	GetComponents() noexcept;
	template <typename T>
	T*	GetComponent()
	{
		static_assert(std::is_base_of_v<Component, T>, "T for GetComponent() must be component");

		for (Component* comp : _components)
		{
			if (dynamic_cast<T*>(comp))
			{
				return static_cast<T*>(comp);
			}
		}
	}

	POINT			GetRenderPos() const noexcept;

	void			SetTag(const std::wstring& tag) noexcept;
	void			SetPosition(POINT pos) noexcept;
	void			SetPosition(LONG x, LONG y) noexcept;
	void			SetX(LONG x) noexcept;
	void			SetY(LONG y) noexcept;
	void			SetSize(INT32 width, INT32 height) noexcept;
	void			SetSize(DSize size) noexcept;
	void			SetPivot(Pivot pivot) noexcept;
	void			SetRect(RECT rect) noexcept;
	void			SetRect(RECT rect, int size) noexcept;

	std::wstring	GetType() const noexcept;
	POINT			GetPosition() const noexcept;
	LONG			GetX() const noexcept;
	LONG			GetY() const noexcept;
	DSize			GetSize() const noexcept;
	INT32			GetWidth() const noexcept;
	INT32			GetHeight() const noexcept;
	Pivot			GetPivot() const noexcept;
	RECT			GetRect(int size) const noexcept;
	RECT			GetRect() const noexcept;
	RECT*			GetRectP() noexcept;
	Scene*			GetScene() noexcept;
	Layer*			GetLayer() noexcept;
private:
	POINT						_position = {};
	DSize						_size = {};
	Pivot						_pivot = Pivot::LeftTop;
	Layer*						_layer = nullptr;
	Scene*						_scene = nullptr;
	RECT						_rect = {};
	std::wstring				_tag = L"";
	std::vector<Component*>		_components;
};