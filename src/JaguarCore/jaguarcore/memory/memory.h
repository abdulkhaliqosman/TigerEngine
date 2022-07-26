#pragma once

#include <utility>
#include <unordered_map>
#include <string>
#include <cassert>

namespace jgr
{
	class Memory
	{
	public:
		static void Startup();
		static void Shutdown();

		static char* Allocate(size_t size);
		static void Deallocate(void* obj);

#ifdef JGR_MEM_DEBUG
		template <typename T>
		static T* DebugRegister(T* mem, const char* name)
		{
			assert(ms_MemDebugMap.find(mem) == ms_MemDebugMap.end());
			ms_MemDebugMap.insert(std::pair<void*, const char*>(mem, name));

			return mem;
		}


		inline static void DebugUnRegister(void* mem)
		{
			auto iter = ms_MemDebugMap.find(mem);
			assert(iter != ms_MemDebugMap.end());
			ms_MemDebugMap.erase(iter);

		}
	private:
		static std::unordered_map<void*, const char*> ms_MemDebugMap;
#endif

	};

	template <typename T, typename ... Args>
	T* New(Args&&... args)
	{
		char* mem = Memory::Allocate(sizeof(T));
		return new (mem) T(std::forward<Args>(args)...);
	}

	template <typename T>
	void Delete(T* obj)
	{
		obj->~T();
		Memory::Deallocate(obj);
	}
}

#ifdef JGR_MEM_DEBUG
#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x
#define LINE_STRING STRINGIZE(__LINE__)

#define jgrDebugNew(ptr) jgr::Memory::DebugRegister(ptr, __FILE__", ("LINE_STRING")");
#define jgrDebugDelete(ptr) jgr::Memory::DebugUnRegister(ptr);
#else
#define jgrDebugNew(ptr, name)
#define jgrDebugDelete(ptr) {}
#endif

#define jgrNew(type, ...) jgrDebugNew(jgr::New<type>(__VA_ARGS__));
#define jgrDelete(mem) jgrDebugDelete(mem); jgr::Delete(mem); 