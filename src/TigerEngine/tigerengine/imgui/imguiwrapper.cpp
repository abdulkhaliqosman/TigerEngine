#include <tigerengine/tigerpch.h>
#include <tigerengine/imgui/imguiwrapper.h>
#include <imgui.h>
#include "optick.h"

namespace tgr
{
	void ImGuiWrapper::Startup()
	{
		OPTICK_EVENT();
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		for (auto* page : m_Pages)
		{
			page->Startup();
		}
	}
	
	void ImGuiWrapper::Update()
	{
		OPTICK_EVENT();
		ImGui::NewFrame();

		if (m_ShowDemoWindow)
		{
			ImGui::ShowDemoWindow(&m_ShowDemoWindow);
		}

		ImGui::Begin("First Window");
		ImGui::Text("Hello, world!");
		ImGui::End();

		for (auto* page : m_Pages)
		{
			bool show = page->GetIsOpened();
			if (show)
			{
				page->Update();
			}

			if (ImGui::BeginMenu(page->GetMenuName()))
			{
				
				ImGui::MenuItem(page->GetMenuItemName(), nullptr, &show);

				page->SetIsOpened(show);
				ImGui::EndMenu();
			}
		}

		ImGui::Render();
	}

	void ImGuiWrapper::Shutdown()
	{

	}

	void ImGuiWrapper::AddImguiPage(jgr::ImguiPage* page)
	{
		m_Pages.push_back(page);
	}
}

