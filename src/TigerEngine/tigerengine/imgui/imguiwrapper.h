#pragma once

#include <jaguarcore/system/isystem.h>
#include <jaguarcore/object/objectvisitor.h>
#include <jaguarcore/imgui/imguipage.h>

namespace tgr
{
	class ImGuiVisitor : public jgr::ObjectVisitor
	{

	};

	class ImGuiWrapper : public iSystem
	{
	public:
		void Startup() override;
		void Update() override;
		void Shutdown() override;

		void AddImguiPage(jgr::ImguiPage* page);
	private:

		bool m_ShowDemoWindow = true;
		std::vector<jgr::ImguiPage*> m_Pages;
	};
}