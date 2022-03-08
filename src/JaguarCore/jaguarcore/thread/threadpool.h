#pragma once

#include <vector> //TODO: Remove all vectors
#include <thread> //TODO: Remove all STL

namespace jgr
{

	class ThreadPool
	{
	public:
		template<typename Func, class...Args>
		void Startup(int count, Func&& f, Args&&... args)
		{
			m_ThreadCount = count;
			m_Threads.reserve(count);
			for (int i = 0; i < count; ++i)
			{
				m_Threads.emplace_back(std::forward<Func>(f), std::forward<Args>(args)...);
			}
		}

		void Shutdown()
		{
			for (int i = 0; i < m_ThreadCount; ++i)
			{
				m_Threads[i].join();
			}
		}

	private:
		int m_ThreadCount = 0;
		std::vector<std::thread> m_Threads;
	};

}
