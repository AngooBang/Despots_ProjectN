#include "Layer.h"
#include "Scene.h"

#include "stdafx.h"
#include "Object/GameObject.h"

Layer::Layer(Scene* scene, const std::wstring& tag, INT32 zOrder)
	:
	_scene(scene),
	_tag { tag },
	_zOrder{ zOrder }
{
	_scene->AddLayer(this);
}

Layer::~Layer()
{
	for (auto& obj : _objects)
	{
		delete obj;
		obj = nullptr;
	}
	_objects.clear();
}

void Layer::Init()
{
	for (GameObject* _object : _objects)
	{
		_object->Init();
	}
}

void Layer::Update()
{
	for (GameObject* _object : _objects)
	{
		_object->Update();
	}
}

void Layer::PhysicsUpdate()
{
	for (GameObject* _object : _objects)
	{
		_object->PhysicsUpdate();
	}
}

void Layer::Render()
{
	for (GameObject* _object : _objects)
	{
		_object->Render();
	}
}

void Layer::Release()
{
	for (GameObject* _object : _objects)
	{
		_object->Release();
	}
}

const Scene* Layer::GetScene() const noexcept
{
	return _scene;
}

std::wstring Layer::GetType() const noexcept
{
	return _tag;
}

INT32 Layer::GetZOrder() const noexcept
{
	return _zOrder;
}

void Layer::AddObject(GameObject* obj)
{
	_objects.push_back(obj);
}

void Layer::RemoveObject(const wstring& tag)
{
	if (tag == L"Item") // Item 태그를 가진 오브젝트 전부 제거
	{
		for (auto iter = _objects.begin(); iter != _objects.end();)
		{
			if ((*iter)->GetType() == tag)
				iter = _objects.erase(iter);
			else
				++iter;
		}
	}
	else
	{
		remove_if(_objects.begin(), _objects.end(),
			[&tag](const GameObject* obj)
			{
				return obj->GetType() == tag;
			});
	}




}

void Layer::RemoveObject(GameObject* obj)
{
	for (auto iter = _objects.begin(); iter != _objects.end();)
	{
		if ((*iter) == obj)
			iter = _objects.erase(iter);
		else
			++iter;
	}
}
