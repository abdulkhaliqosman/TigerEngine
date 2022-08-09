#pragma once

namespace jgr
{
	class iApp
	{
	public:
		virtual ~iApp() {}
		virtual void Run() = 0;

		virtual void OnWindowClose() = 0;
		virtual void OnWindowDestroyed() = 0;
	};
}
