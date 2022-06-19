#pragma once

namespace jgr
{
	class ImguiPage
	{
	public:
		virtual void Startup() = 0;
		virtual void Update() = 0;

		virtual const char* GetMenuName() = 0;
		virtual const char* GetMenuItemName() = 0;

		bool GetIsOpened() const { return m_IsOpened; }
		void SetIsOpened(bool value) { m_IsOpened = value; }

	private:

		bool m_IsOpened = false;
	};
}