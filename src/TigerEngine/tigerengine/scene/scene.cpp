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
#include <tigerengine/gameplay/cameramovementcomponent.h>
#include <leopardgraphics/component/cameracomponent.h>
#include <tigerengine/gameplay/playeractorcomponent.h>
#include "wolfnetworking/system/inetworksystem.h"
#include <wolfnetworking/netmsg/netmsghandler.h>
#include <tigerengine/bulletphysics/bulletphysics.h>

namespace tgr
{
	static void InitPlayerActorComponent(Engine* engine, PlayerActorComponent& pac)
	{
		static int id = 0;
		pac.SetUserId(++id); // set user id to 1 ++, 0 is server (we assume headed but non-player server)

		std::function<void(const MovePlayerNetMsg&)> func
			= [&pac](const MovePlayerNetMsg& msg)
		{
			pac.OnReceive(msg);
		};

		engine->GetNetwork()->GetMsgHandler().RegisterNetMsgType(func);
	}

	static jgr::GameObject* CreateCharacter(const vec3& pos, Engine* engine, float startTime)
	{
		Scene* scene = engine->GetScene();

		auto* go = scene->CreateGameObject();
		auto* transform = scene->CreateTransformComponent(go);
		
		transform->SetLocalPosition(pos);
		transform->SetLocalScale(vec3(1.0f, 1.0f, 1.0f));
		transform->SetLocalRotation(quat::FromEulerAngles(jgr::EulerAngles{ 0.0f, 180.0f, 0.0f }));

		auto* anim = engine->GetAnimation()->CreateAnimationComponent();

		// TODO: reuse same meshes
		auto* animClip = engine->GetAnimation()->LoadClip("./assets/animations/jumpanim.glb");
		auto* animPose = engine->GetAnimation()->ClonePose("./assets/meshes/testmesh.glb");
		
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

		auto* agent = engine->GetScene()->GetAgentManager().CreateAgentComponent(go);

		auto* actor = scene->CreateGenericComponent<PlayerActorComponent>(go);
		actor->SetGameNetwork(engine->GetGameNetwork());
		actor->SetNetwork(engine->GetNetwork());
		InitPlayerActorComponent(engine, *actor);

		return go;
	}

	static jgr::GameObject* CreateCamera(Engine* engine)
	{
		auto* go = engine->GetScene()->CreateGameObject();
		auto* transform = engine->GetScene()->CreateTransformComponent(go);

		transform->SetLocalPosition(vec3(0.0f, 0.0f, 5.0f));

		auto* cc = engine->GetGraphics()->CreateCameraComponent();
		go->AddComponent(cc);

		engine->GetGraphics()->SetActiveCamera(cc);

		auto* cmc = engine->GetScene()->CreateGenericComponent<CameraMovementComponent>(go);

		return go;
	}

	static jgr::GameObject* CreatePhysicsCube(Engine& engine, const vec3& pos, const vec3& halfextents, float mass)
	{
		auto* go = engine.GetScene()->CreateGameObject();
		auto* transform = engine.GetScene()->CreateTransformComponent(go);

		
		transform->SetLocalPosition(pos);

		auto* gc = engine.GetGraphics()->CreateGraphicsComponent();
		go->AddComponent(gc);

		lpd::Cube* cube = engine.GetGraphics()->CreateCube();
		cube->SetScale(halfextents * 2.0f);

		gc->AddShape(cube);

		BulletCollisionShape* boxShape = engine.GetPhysics()->CreateBoxShape(vec3::Zero(), quat::Identity(), halfextents, 1.0f);
		BulletRigidBody* rb = engine.GetPhysics()->CreateRigidBody(pos, quat::Identity(), mass, *boxShape);
		go->AddComponent(rb);

		return go;
	}

	Scene::Scene(iEngine& engine) 
		:iScene(engine), m_AgentManager(*this) 
	{

	}

	void Scene::Setup()
	{
		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 2; ++j)
			{
				CreateCharacter(vec3(i - 1.0f, 0.0f, j - 1.0f), m_Engine, i * 0.01f + j * 0.1f);
			}
		}
		
		CreateCamera(m_Engine);
		

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				CreatePhysicsCube(*m_Engine, vec3(i - 1.0f, 1.0f, j - 1.0f), vec3(0.2f, 0.2f, 0.2f), 1.0f);
			}
		}

		CreatePhysicsCube(*m_Engine, vec3(1.0f, -1.0f, 1.0f), vec3(10.0f, 0.1f, 10.0f), 0.0f);
		m_AgentManager.Setup();
	}

	void Scene::Teardown()
	{
		for (auto* go : m_GameObjects)
		{
			jgr::Delete(go);
		}

		for (auto* transform : m_TransformComponents)
		{
			jgr::Delete(transform);
		}

		m_AgentManager.Teardown();
	}

	void Scene::StartScene()
	{

	}

	void Scene::StopScene()
	{

	}

	void Scene::Update()
	{
		OPTICK_EVENT();
		m_AgentManager.Update();

		for (auto* comp : m_GenericComponents)
		{
			comp->Update();
		}

		for (auto* transform : m_TransformComponents)
		{
			transform->Update();
		}
	}

	jgr::GameObject* Scene::CreateGameObject()
	{
		auto* go = jgr::New<jgr::GameObject>();
		m_GameObjects.push_back(go);
		go->SetScene(this);
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