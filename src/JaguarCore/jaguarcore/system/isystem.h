#pragma once

namespace jgr
{
	class iSystem
	{
	public:
		virtual ~iSystem() {}

		virtual void Startup() = 0;
		virtual void Update() = 0;
		virtual void Shutdown() = 0;
	};
}