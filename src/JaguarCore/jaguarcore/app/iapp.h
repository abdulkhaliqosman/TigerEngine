#pragma once

namespace jgr
{
	class iApp
	{
	public:
		virtual void Run() = 0;

		virtual void OnWindowClose() = 0;
		virtual void OnWindowDestroyed() = 0;
	};
}
