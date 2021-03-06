#include "stdafx.h"
#include "Component/Component.h"
#include "Scene/Layer.h"

#include "GameObject.h"

GameObject::GameObject(Scene* scene, Layer* layer, const wstring& tag)
	:
	_scene{ scene },
	_layer{ layer },
	_tag{ tag }
{
	_layer->AddObject(this);
}

GameObject::~GameObject() noexcept
{

	// 같은컴포넌트가 여러개 있을때 다 지워버리기 때문에 nullptr를 delete하는 에러가 발생
	//for (auto& comp : _components)
	//{
	//	delete comp;
	//	comp = nullptr;
	//} 
	Component* pTemp = nullptr;
	for (auto it = _components.begin(); it != _components.end(); )
	{
		pTemp = (*it);
		it = _components.erase(it);
		delete pTemp;
	}
	_components.clear();
	_layer = nullptr;
	_scene = nullptr;
}

void GameObject::Init()
{
	for (Component* comp : _components)
	{
		comp->Init();
	}
}

void GameObject::Update()
{
	for (Component* comp : _components)
	{
		comp->Update();
	}
}

void GameObject::PhysicsUpdate()
{
	for (Component* comp : _components)
	{
		comp->PhysicsUpdate();
	}
}

void GameObject::Render()
{
	for (Component* comp : _components)
	{
		comp->Render();
	}
}

void GameObject::Release()
{
	for (Component* comp : _components)
	{
		comp->Release();
	}
}

void GameObject::AddComponent(Component* component)
{
	_components.push_back(component);

	sort(_components.begin(), _components.end(),
		[](const Component* lhs, const Component* rhs)
		{
			return lhs->GetOrder() < rhs->GetOrder();
		});
}

void GameObject::RemoveComponent(Component* component)
{
	remove(_components.begin(), _components.end(), component);
}

POINT GameObject::GetRenderPos() const noexcept
{
	POINT temp = { _size.Width * _pivot.X, _size.Height * _pivot.Y };

	return POINT{ _position.x - temp.x, _position.y - temp.y };
}

void GameObject::SetTag(const wstring& tag) noexcept
{
	_tag = tag;
}

void GameObject::SetPosition(POINT pos) noexcept
{
	_position = pos;
}

void GameObject::SetPosition(LONG x, LONG y) noexcept
{
	_position = POINT{ x, y };
}

wstring GameObject::GetType() const noexcept
{
	return _tag;
}

POINT GameObject::GetPosition() const noexcept
{
	return _position;
}

void GameObject::SetX(LONG x) noexcept
{
	_position.x = x;
}

LONG GameObject::GetX() const noexcept
{
	return _position.x;
}

void GameObject::SetY(LONG y) noexcept
{
	_position.y = y;
}

void GameObject::SetSize(INT32 width, INT32 height) noexcept
{
	_size = DSize{ width, height };
}

void GameObject::SetSize(DSize size) noexcept
{
	_size = size;
}

void GameObject::SetPivot(Pivot pivot) noexcept
{
	_pivot = pivot;
}

void GameObject::SetRect(RECT rect) noexcept
{
	_rect = rect;
}

void GameObject::SetRect(RECT rect, int size) noexcept
{
	// 사이즈만큼 키워서 멤버에 입력
	_rect = { rect.left - size, rect.top - size, rect.right + size, rect.bottom + size };
}

LONG GameObject::GetY() const noexcept
{
	return _position.y;
}

DSize GameObject::GetSize() const noexcept
{
	return _size;
}

INT32 GameObject::GetWidth() const noexcept
{
	return _size.Width;
}

INT32 GameObject::GetHeight() const noexcept
{
	return _size.Height;
}

Pivot GameObject::GetPivot() const noexcept
{
	return _pivot;
}

RECT GameObject::GetRect(int size) const noexcept
{
	// 사이즈만큼 키워서 반환해줌, 멤버변수엔 영향x
	RECT tempRect = { _rect.left - size, _rect.top - size, _rect.right + size, _rect.bottom + size };
	return tempRect;
}

RECT GameObject::GetRect() const noexcept
{
	return _rect;
}

RECT* GameObject::GetRectP() noexcept
{
	return &_rect;
}

Scene* GameObject::GetScene() noexcept
{
	return _scene;
}

Layer* GameObject::GetLayer() noexcept
{
	return _layer;
}

vector<Component*>& GameObject::GetComponents() noexcept
{
	return _components;
}
