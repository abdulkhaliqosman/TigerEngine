#include <tigerengine/tigerpch.h>
#include <tigerengine/scene/scene.h>

#include <tigerengine/engine/engine.h>
#include "jaguarcore/gameobject/gameobject.h"
#include <leopardgraphics/component/graphicscomponent.h>
#include <leopardgraphics/graphics/igraphicssystem.h>

namespace tgr
{
	static jgr::GameObject* CreateCube(const vec3& pos, Engine* engine)
	{
		auto go = jgr::New<jgr::GameObject>();

		auto transform = jgr::New<jgr::TransformComponent>();
		go->AddComponent(transform);
		go->SetTransform(transform);
		transform->SetPosition(pos);

		auto render = engine->GetGraphics()->CreateGraphicsComponent();
		//render->AddShape();
		go->AddComponent(render);

		return go;
	}

	void Scene::Startup()
	{
		m_GameObjects.push_back(CreateCube(vec3(0.2f,0.2f,0.2f), m_Engine));

		
	}

	void Scene::Update()
	{

	}

	void Scene::Shutdown()
	{

	}

}