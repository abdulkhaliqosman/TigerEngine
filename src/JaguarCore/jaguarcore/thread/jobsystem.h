#pragma once

#include <jaguarcore/engine/ienginesystem.h>
#include "jaguarcore/thread/jobqueue.h"
#include "jaguarcore/thread/threadpool.h"

namespace jgr
{
	class JobSystem : public iEngineSystem
	{
	public:
		inline JobSystem(iEngine& engine) : iEngineSystem(engine) {}
		inline ~JobSystem() {}

		void Setup() override;
		void Teardown() override;

		void StartScene() override;
		void StopScene() override;

		void Update() override;

		void PushJob(Job* job);

	private:
		ThreadPool m_ThreadPool;
		JobQueue m_JobQueue;
		bool m_IsRunning = false;
	};
}