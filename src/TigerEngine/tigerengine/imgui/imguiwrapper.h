#pragma once

#include <jaguarcore/object/objectvisitor.h>
#include <jaguarcore/imgui/imguipage.h>

namespace tgr
{
	class ImGuiVisitor : public jgr::ObjectVisitor
	{

	};

	class ImGuiWrapper : public iEngineSystem
	{
	public:
		inline ImGuiWrapper(iEngine& engine) : iEngineSystem(engine) {}
		inline ~ImGuiWrapper() {}

		void Setup() override;
		void Teardown() override;

		void StartScene() override;
		void StopScene() override;

		void Update() override;

		void AddImguiPage(jgr::ImguiPage* page);
	private:

		bool m_ShowDemoWindow = true;
		std::vector<jgr::ImguiPage*> m_Pages;
	};
}