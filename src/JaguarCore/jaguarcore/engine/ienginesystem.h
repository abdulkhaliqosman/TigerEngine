#pragma once

namespace jgr
{
	class JobSystem;
	class iEngine;

	class iEngineSystem : public iSystem
	{
	public:
		inline iEngineSystem(iEngine& engine) :m_Engine(engine) {}
		virtual ~iEngineSystem() {}

		virtual void StartScene() = 0;
		virtual void StopScene() = 0;

		inline iEngine& GetEngine() { return m_Engine; }
		inline const iEngine& GetEngine() const { return m_Engine; }

		inline JobSystem& GetJobSystem() { return m_Engine.GetJobSystem(); }

	private:
		iEngine& m_Engine;
	};
}
