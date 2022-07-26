#include <leopardgraphics/leopardpch.h>
#include "glgraphicssystem.h"

#include <leopardgraphics/display/idisplay.h>
#include "leopardgraphics/loader/gltfmeshloader.h"
#include "draw.h"

#include <leopardgraphics/component/graphicscomponent.h>
#include <leopardgraphics/component/cameracomponent.h>
#include <jaguarcore/gameobject/gameobject.h>
#include <leopardgraphics/shapes/mesh.h>
#include "leopardgraphics/shapes/skeletalmesh.h"
#include "optick.h"

namespace lpd
{
	iGraphicsSystem* iGraphicsSystem::CreateGraphicsSystem()
	{
		return jgrNew(GLGraphicsSystem);
	}

	void GLGraphicsSystem::Startup()
	{
		m_VertexArray.Load(1);
		m_Shader.Load("./assets/shaders/static.vert", "./assets/shaders/lit.frag");

		m_VertexArray.Bind(0);
		m_Cube.Set();
		for (CameraComponent* cc : m_CameraComponents)
		{
			cc->Startup();
		}

		for (GraphicsComponent* gc : m_GraphicsComponents)
		{
			gc->Startup();
		}


		m_VertexArray.Unbind();
	}

	void GLGraphicsSystem::Update()
	{
		OPTICK_EVENT();
		Rect clientRect = m_Display->GetClientRect();

		int clientWidth = clientRect.right - clientRect.left;
		int clientHeight = clientRect.bottom - clientRect.top;
		glViewport(0, 0, clientWidth, clientHeight);

		ClearScreen();

		float aspect = (float)clientWidth / (float)clientHeight;

		m_Shader.Bind();
		m_VertexArray.Bind(0);

		auto transform = mat4::Identity();
		transform[0][0] = 0.1f;
		transform[1][1] = 0.1f;
		transform[2][2] = 0.1f;

		mat4 view = mat4::Identity();
		mat4 projection = mat4::Identity();

		for (CameraComponent* cc : m_CameraComponents)
		{
			cc->Update();
		}

		if (m_ActiveCamera)
		{
			projection = m_ActiveCamera->GetProjectionMatrix();
			view = m_ActiveCamera->GetGameObject()->GetTransform()->GetGlobalTransform().Inverse();
		}

		// TODO: sort by shape
		Uniform<mat4>::Set(m_Shader.GetUniform("view"), view);
		Uniform<mat4>::Set(m_Shader.GetUniform("projection"), projection);
		Uniform<vec3>::Set(m_Shader.GetUniform("lightPos"), m_ActiveCamera->GetGameObject()->GetTransform()->GetLocalPosition());
		

		for (GraphicsComponent* gc : m_GraphicsComponents)
		{
			gc->Render(m_Shader);
		}

		m_Cube.GetPosAttrib().BindTo(m_Shader.GetAttribute("position"));
		Uniform<mat4>::Set(m_Shader.GetUniform("model"), transform);
		Draw(m_Cube.GetElementBuffer(), DrawMode::Triangles);

		m_VertexArray.Unbind();
		m_Shader.Unbind();
	}

	void GLGraphicsSystem::Shutdown()
	{
		m_VertexArray.Unload();

		for (auto* elem : m_GraphicsComponents)
		{
			elem->Shutdown();
			jgr::Delete(elem);
		}

		for (auto* elem : m_CameraComponents)
		{
			elem->Shutdown();
			jgr::Delete(elem);
		}

		for (auto* elem : m_Shapes)
		{
			jgr::Delete(elem);
		}
	}

	void GLGraphicsSystem::SetDisplay(iDisplay* value) { m_Display = value; }
	iDisplay* GLGraphicsSystem::GetDisplay() { return m_Display; }

	GraphicsComponent* GLGraphicsSystem::CreateGraphicsComponent()
	{
		auto result = jgrNew(lpd::GraphicsComponent);
		m_GraphicsComponents.push_back(result);
		return result;
	}

	CameraComponent* GLGraphicsSystem::CreateCameraComponent()
	{
		auto result = jgr::New<lpd::CameraComponent>();
		m_CameraComponents.push_back(result);
		return result;
	}

	void GLGraphicsSystem::ClearScreen()
	{
		glEnable(GL_DEPTH_TEST);
		// glEnable(GL_CULL_FACE);
		// glPointSize(5.0f);

		glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	MeshGroup* GLGraphicsSystem::LoadMesh(const std::string& path)
	{
		for (auto* shape : m_Shapes)
		{
			if (shape->GetPath() == path)
			{
				return dynamic_cast<MeshGroup*>(shape);
			}
		}

		lpd::GLTFMeshLoader meshLoader;
		auto* meshGroup = meshLoader.LoadMesh(path);
		meshGroup->SetPath(path);

		m_Shapes.push_back(meshGroup);

		return meshGroup;
	}

	SkeletalMesh* GLGraphicsSystem::CreateSkeletalMesh()
	{
		auto result = jgr::New<SkeletalMesh>();
		m_SkeletalMeshes.push_back(result);
		return result;
	}
}