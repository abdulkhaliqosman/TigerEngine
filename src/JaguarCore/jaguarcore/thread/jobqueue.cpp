#include <jaguarcore/jaguarpch.h>
#include "jaguarcore/thread/jobqueue.h"

//TODO: don't use locks
namespace jgr
{
	void JobQueue::PushJob(Job* job)
	{
		std::lock_guard<std::mutex> lock(m_JobMutex);
		m_Jobs.push_back(job);
	}

	Job* JobQueue::PopJob()
	{
		std::lock_guard<std::mutex> lock(m_JobMutex);

		if (m_Jobs.empty())
		{
			return nullptr;
		}

		Job* job = m_Jobs.back();
		m_Jobs.pop_back();

		return job;
	}

	bool JobQueue::Empty() const
	{
		std::lock_guard<std::mutex> lock(m_JobMutex);
		return m_Jobs.empty();
	}
}