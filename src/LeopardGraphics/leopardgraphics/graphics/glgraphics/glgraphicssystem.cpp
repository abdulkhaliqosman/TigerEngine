#include <leopardgraphics/leopardpch.h>
#include "glgraphicssystem.h"

#include <leopardgraphics/display/idisplay.h>
#include "leopardgraphics/loader/gltfmeshloader.h"
#include "draw.h"

#include <leopardgraphics/component/graphicscomponent.h>

namespace lpd
{
	iGraphicsSystem* iGraphicsSystem::CreateGraphicsSystem()
	{
		return jgr::New<GLGraphicsSystem>();
	}

	void GLGraphicsSystem::Startup()
	{
		GLTFMeshLoader meshLoader;

		m_VertexArray.Load(1);
		m_Shader.Load("./assets/shaders/static.vert", "./assets/shaders/lit.frag");


		m_VertexArray.Bind(0);
		m_Cube.Set();
		m_VertexArray.Unbind();


	}

	void GLGraphicsSystem::Update()
	{
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

		// TODO: sort by shape
		

		for (const GraphicsComponent* gc : m_GraphicsComponents)
		{

		}

		m_Cube.GetPosAttrib().BindTo(m_Shader.GetAttribute("position"));
		Uniform<mat4>::Set(m_Shader.GetUniform("model"), transform);
		Uniform<mat4>::Set(m_Shader.GetUniform("view"), view);
		Uniform<mat4>::Set(m_Shader.GetUniform("projection"), projection);
		Draw(m_Cube.GetElementBuffer(), DrawMode::Triangles);

		m_VertexArray.Unbind();
		m_Shader.Unbind();
	}

	void GLGraphicsSystem::Shutdown()
	{
		m_VertexArray.Unload();
	}

	void GLGraphicsSystem::SetDisplay(iDisplay* value) { m_Display = value; }
	iDisplay* GLGraphicsSystem::GetDisplay() { return m_Display; }

	GraphicsComponent* GLGraphicsSystem::CreateGraphicsComponent()
	{
		auto result = jgr::New<lpd::GraphicsComponent>();

		m_GraphicsComponents.push_back(result);

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
}