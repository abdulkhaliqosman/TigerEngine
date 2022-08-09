#include <tigerengine/tigerpch.h>
#include <tigerengine/imgui/windows/winimguiwrapper.h>
#include <imgui.h>

#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_opengl3.h"
#include "optick.h"

namespace tgr
{
	void WinImGuiWrapper::Setup()
	{
		ImGuiWrapper::Setup();
		ImGui_ImplWin32_Init(m_Context->GetHWND());
		ImGui_ImplOpenGL3_Init(nullptr);
	}

	void WinImGuiWrapper::Update()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGuiWrapper::Update();
		
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

	void WinImGuiWrapper::Teardown()
	{

	}
}