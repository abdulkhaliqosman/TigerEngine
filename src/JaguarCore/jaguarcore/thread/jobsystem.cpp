#include <jaguarcore/jaguarpch.h>
#include <jaguarcore/thread/jobsystem.h>
#include "optick.h"
#include <chrono>
#include <thread>

namespace jgr
{
	void JobSystem::Startup()
	{
		m_IsRunning = true;
		auto lambda = [this]()
		{
			OPTICK_THREAD("Worker");
			while (m_IsRunning)
			{
				Job* job = m_JobQueue.PopJob();
				if (job == nullptr)
				{
					continue;
					// using namespace std::chrono_literals;
					// std::this_thread::sleep_for(1ms);
				}
				else
				{
					job->Execute();
				}
			}
		};

		m_ThreadPool.Startup(9, lambda); // TODO: don't hard code threads
	}

	void JobSystem::Update()
	{
		OPTICK_EVENT();
		while (!m_JobQueue.Empty());
	}

	void JobSystem::Shutdown()
	{
		m_IsRunning = false;
		m_ThreadPool.Shutdown();
	}

	void JobSystem::PushJob(Job* job)
	{
		m_JobQueue.PushJob(job);
	}
}