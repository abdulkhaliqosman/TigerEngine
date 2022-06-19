#pragma once

#include <jaguarcore\system\isystem.h>

namespace jgr
{
	class JobSystem;
	class iInput;

	class iEngine : public iSystem
	{
	public:
		inline iEngine() {}

		virtual ~iEngine() {}

		virtual JobSystem& GetJobSystem() = 0;
		virtual iInput& GetInput() = 0;
	};

	class EngineSystem : public iSystem
	{
	public:
		inline EngineSystem(iEngine& iEngine) :m_Engine(iEngine) {}

		virtual ~EngineSystem() {}

		inline iEngine& GetEngine() { return m_Engine; }
		inline const iEngine& GetEngine() const { return m_Engine; }

		inline JobSystem& GetJobSystem() { return m_Engine.GetJobSystem(); }

	private:

		iEngine& m_Engine;
	};
}
