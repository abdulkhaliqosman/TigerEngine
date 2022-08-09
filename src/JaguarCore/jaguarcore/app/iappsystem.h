#pragma once

#include <jaguarcore/app/iapp.h>
#include <jaguarcore/system/isystem.h>

namespace jgr
{
	class iAppSystem : public iSystem
	{
	public:
		inline iAppSystem(iApp& app) :m_App(app) {}
		virtual ~iAppSystem() {}

		inline iApp& GetApp() { return m_App; }
		inline const iApp& GetApp() const { return m_App; }

	private:
		iApp& m_App;
	};
}
