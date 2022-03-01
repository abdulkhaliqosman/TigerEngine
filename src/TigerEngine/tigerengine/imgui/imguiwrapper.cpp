#include <tigerengine/tigerpch.h>
#include <tigerengine/imgui/imguiwrapper.h>
#include <imgui.h>

namespace tgr
{
	void ImGuiWrapper::Startup()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
	}
	
	void ImGuiWrapper::Update()
	{
		ImGui::NewFrame();

		if (m_ShowDemoWindow)
		{
			ImGui::ShowDemoWindow(&m_ShowDemoWindow);
		}

		ImGui::Begin("First Window");
		ImGui::Text("Hello, world!");
		ImGui::End();
		ImGui::Render();
	}

	void ImGuiWrapper::Shutdown()
	{

	}
}

