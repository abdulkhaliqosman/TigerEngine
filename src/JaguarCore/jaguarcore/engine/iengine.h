#pragma once

#include <jaguarcore/app/iappsystem.h>

namespace jgr
{
	class JobSystem;
	class iInput;

	class iEngine : public iAppSystem
	{
	public:
		inline iEngine(iApp& app) :iAppSystem{app} {}
		virtual ~iEngine() {}

		virtual JobSystem& GetJobSystem() = 0;
		virtual iInput& GetInput() = 0;
	};
}
