#include <tigerengine/tigerpch.h>
#include <tigerengine/scene/scene.h>

#include <tigerengine/engine/engine.h>
#include "jaguarcore/gameobject/gameobject.h"
#include <leopardgraphics/component/graphicscomponent.h>
#include <leopardgraphics/graphics/igraphicssystem.h>
#include <leopardgraphics/shapes/mesh.h>
#include <leopardgraphics/loader/gltfmeshloader.h>
#include "leopardgraphics/shapes/skeletalmesh.h"

#include <lionanimation/system/animationsystem.h>
#include <lionanimation/component/animationcomponent.h>
#include "optick.h"

namespace tgr
{
	static jgr::GameObject* CreateCharacter(const vec3& pos, Engine* engine, float startTime)
	{
		auto* go = engine->GetScene()->CreateGameObject();
		auto* transform = engine->GetScene()->CreateTransformComponent(go);
		
		transform->SetPosition(pos);
		transform->SetScale(vec3(0.2f, 0.2f, 0.2f));
		transform->SetRotation(quat::FromEulerAngles(jgr::EulerAngles{ 0.0f, 180.0f, 0.0f }));

		auto* anim = engine->GetAnimation()->CreateAnimationComponent();

		// TODO: reuse same meshes
		auto* animClip = engine->GetAnimation()->LoadClip("./assets/animations/jumpanim.glb");
		auto* animPose = engine->GetAnimation()->LoadPose("./assets/meshes/testmesh.glb");
		
		anim->SetClip(animClip);
		anim->SetPose(animPose);
		anim->SetLoop(true);
		anim->StartAnim();
		anim->SetTimer(startTime);
		go->AddComponent(anim);

		auto* meshGroup = engine->GetGraphics()->LoadMesh("./assets/meshes/testmesh.glb");
		auto* render = engine->GetGraphics()->CreateGraphicsComponent();
		auto* skeletalMesh = engine->GetGraphics()->CreateSkeletalMesh();
		skeletalMesh->SetMesh(meshGroup->m_Meshes[0]);
		skeletalMesh->SetPose(animPose);

		render->AddShape(skeletalMesh);
		go->AddComponent(render);

		return go;
	}

	static jgr::GameObject* CreateCamera(Engine* engine)
	{
		auto* go = engine->GetScene()->CreateGameObject();
		auto* transform = engine->GetScene()->CreateTransformComponent(go);
	}

	void Scene::Startup()
	{
		for (int i = 0; i < 30; ++i)
		{
			for (int j = 0; j < 30; ++j)
			{
				CreateCharacter(vec3(i * 0.05f - 1.0f, j * 0.05f - 1.0f, 0.2f), m_Engine, i * 0.01f + j * 0.1f);
			}
		}
		
	}

	void Scene::Update()
	{
		OPTICK_EVENT();
		for (auto* transform : m_TransformComponents)
		{
			transform->Update();
		}
	}

	void Scene::Shutdown()
	{
		for (auto* go : m_GameObjects)
		{
			jgr::Delete(go);
		}

		for (auto* transform : m_TransformComponents)
		{
			jgr::Delete(transform);
		}
	}

	jgr::GameObject* Scene::CreateGameObject()
	{
		auto* go = jgr::New<jgr::GameObject>();
		m_GameObjects.push_back(go);

		return go;
	}

	jgr::TransformComponent* Scene::CreateTransformComponent(jgr::GameObject* gameObject)
	{
		auto* transform = jgr::New<jgr::TransformComponent>();
		gameObject->AddComponent(transform);
		gameObject->SetTransform(transform);

		m_TransformComponents.push_back(transform);

		return transform;
	}

}