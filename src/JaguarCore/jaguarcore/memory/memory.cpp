#include <jaguarcore/jaguarpch.h>
#include <jaguarcore/memory/memory.h>
#include <cassert>

namespace jgr
{
	std::unordered_map<void*, const char*> Memory::ms_MemDebugMap;

	class MemoryAllocator
	{
	public:
		char* Allocate(size_t size);
		void Deallocate(void* memory);

		void Startup();
		void Shutdown();

	private:
		// hardcode to 2GB

		static constexpr size_t CACHE_SIZE = 64;
		static constexpr size_t PAGE_SIZE = 4096;
		static constexpr size_t ALLOC_SIZE = 2048ull * 1024ull * 1024ull;

		static constexpr size_t CACHE_COUNT = PAGE_SIZE / CACHE_SIZE;
		static constexpr size_t PAGE_COUNT = ALLOC_SIZE / PAGE_SIZE;

		struct alignas(CACHE_SIZE) MemoryCache
		{
			char data[CACHE_SIZE];
		};

		struct alignas(PAGE_SIZE) MemoryPage
		{
			MemoryCache data[CACHE_COUNT];
		};

		MemoryPage* m_Chunks = nullptr;
		MemoryPage* m_Next = nullptr;
		size_t m_AllocCount = 0;
	};

	static MemoryAllocator gs_MemoryAllocator;

	void MemoryAllocator::Startup()
	{
		m_Chunks = new MemoryPage[PAGE_COUNT];
		m_AllocCount = 0;
	}

	void MemoryAllocator::Shutdown()
	{
		assert(m_AllocCount == 0);

	}

	char* MemoryAllocator::Allocate(size_t size)
	{
		m_AllocCount++;
		return nullptr;
	}

	void MemoryAllocator::Deallocate(void* memory)
	{
		m_AllocCount--;
	}

	void Memory::Startup()
	{
		gs_MemoryAllocator.Startup();
	}

	void Memory::Shutdown()
	{
		for (auto iter : ms_MemDebugMap)
		{
			JgrLogError("%s", iter.second);
		}

		gs_MemoryAllocator.Shutdown();
	}

	char* Memory::Allocate(size_t size)
	{
		// return gs_MemoryAllocator.Allocate(size);
		return new char[size];
	}

	void Memory::Deallocate(void* obj)
	{
		// gs_MemoryAllocator.Deallocate(obj);
		delete[] obj;
	}
}