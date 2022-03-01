#pragma once

#include <tigerengine/imgui/imguiwrapper.h>
#include <tigerengine/app/windows/winglcontext.h>

namespace tgr
{
	class WinImGuiWrapper : public ImGuiWrapper
	{
	public:
		void Startup() override;
		void Update() override;
		void Shutdown() override;

		void SetContext(WinGLContext* value) { m_Context = value; }
	private:
		WinGLContext* m_Context;
	};
}