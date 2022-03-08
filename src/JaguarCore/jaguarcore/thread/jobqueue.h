#pragma once
#include <vector> //TODO: Remove all vectors
#include <mutex>
#include "optick.h"
namespace jgr
{
	class Job
	{
	public:
		virtual ~Job(){}
		virtual void Execute() = 0;
		inline void Nop() { OPTICK_EVENT(); }
	};

	class JobQueue
	{
	public:
		void PushJob(Job* job);
		Job* PopJob();
		bool Empty() const;
	private:
		mutable std::mutex m_JobMutex;
		std::vector<Job*> m_Jobs;
	};
}