#include "Scene.h"
#include "Layer.h"

#include "stdafx.h"

Scene::Scene()
{

	Layer* backLayer = new Layer(this, L"Back", 1);
	Layer* mapLayer = new Layer(this, L"Map", 2);
	Layer* objectLayer = new Layer(this, L"Object", 3);
	Layer* shopLayer = new Layer(this, L"Shop", 3);
	Layer* uiLayer = new Layer(this, L"UI", 100);
}

Scene::~Scene()
{
	for (auto& layer : _layers)
	{
		delete layer;
		layer = nullptr;
	}
	_layers.clear();
}

void Scene::Init()
{
	for (Layer* layer : _layers)
	{
		layer->Init();
	}
}

void Scene::Update()
{
	for (Layer* layer : _layers)
	{
		layer->Update();
	}
}

void Scene::PhysicsUpdate()
{
	for (Layer* layer : _layers)
	{
		layer->PhysicsUpdate();
	}
}

void Scene::Render()
{
	for (Layer* layer : _layers)
	{
		layer->Render();
	}
}

void Scene::Release()
{
	for (Layer* layer : _layers)
	{
		layer->Release();
	}
}

void Scene::AddLayer(Layer* layer)
{
	_layers.push_back(layer);
	sort(_layers.begin(), _layers.end(),
		[](const Layer* lhs, const Layer* rhs)
		{
			return lhs->GetZOrder() < rhs->GetZOrder();
		});
}

void Scene::RemoveLayer(const std::wstring& tag)
{
	remove_if(_layers.begin(), _layers.end(),
		[&tag](const Layer* layer)
		{
			return layer->GetType() == tag;
		});
}

Layer* Scene::FindLayer(const std::wstring& tag)
{
	auto iter = find_if(_layers.begin(), _layers.end(),
		[&tag](const Layer* layer)
		{
			return layer->GetType() == tag;
		});

	if (iter == _layers.end())
	{
		return nullptr;
	}
	else
	{
		return *iter;
	}
}
