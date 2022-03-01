#include <tigerengine/tigerpch.h>
#include <tigerengine/scene/scene.h>

#include <tigerengine/engine/engine.h>
#include "jaguarcore/gameobject/gameobject.h"
#include <leopardgraphics/component/graphicscomponent.h>
#include <leopardgraphics/graphics/igraphicssystem.h>
#include <leopardgraphics/shapes/mesh.h>
#include <leopardgraphics/loader/gltfmeshloader.h>

namespace tgr
{
	static jgr::GameObject* CreatePlayer(const vec3& pos, Engine* engine)
	{
		auto go = jgr::New<jgr::GameObject>();

		auto transform = jgr::New<jgr::TransformComponent>();
		go->AddComponent(transform);
		go->SetTransform(transform);
		transform->SetPosition(pos);
		lpd::GLTFMeshLoader meshLoader;
		
		auto meshGroup = meshLoader.LoadMesh("./assets/meshes/testmesh.glb");

		auto render = engine->GetGraphics()->CreateGraphicsComponent();
		render->AddShape(meshGroup);
		go->AddComponent(render);

		return go;
	}

	void Scene::Startup()
	{
		m_GameObjects.push_back(CreatePlayer(vec3(-0.2f,-0.2f,0.2f), m_Engine));

		
	}

	void Scene::Update()
	{
		for (auto* go : m_GameObjects)
		{
			go->GetTransform()->Update();
		}
	}

	void Scene::Shutdown()
	{

	}

}