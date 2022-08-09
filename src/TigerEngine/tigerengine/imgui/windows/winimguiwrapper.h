#pragma once

#include <tigerengine/imgui/imguiwrapper.h>
#include <tigerengine/app/windows/winglcontext.h>

namespace tgr
{
	class WinImGuiWrapper : public ImGuiWrapper
	{
	public:
		inline WinImGuiWrapper(iEngine& engine) : ImGuiWrapper(engine) {}
		inline ~WinImGuiWrapper() {}

		void Setup() override;
		void Update() override;

		void Teardown() override;

		void SetContext(WinGLContext* value) { m_Context = value; }
	private:
		WinGLContext* m_Context;
	};
}