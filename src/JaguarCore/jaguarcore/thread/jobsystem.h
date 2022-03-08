#pragma once

#include "jaguarcore/system/isystem.h"
#include "jaguarcore/thread/jobqueue.h"
#include "jaguarcore/thread/threadpool.h"

namespace jgr
{
	class JobSystem : public iSystem
	{
	public:
		void Startup() override;
		void Update() override;
		void Shutdown() override;

		void PushJob(Job* job);

	private:
		ThreadPool m_ThreadPool;
		JobQueue m_JobQueue;
		bool m_IsRunning = false;
	};
}