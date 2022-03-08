#pragma once

#include <utility>

namespace jgr
{
	class Memory
	{
	public:
		static void Startup();
		static void Shutdown();

		static char* Allocate(size_t size);
		static void Deallocate(void* obj);
	};

	template <typename T, typename ... Args>
	T* New(Args&&... args)
	{
		char* mem = Memory::Allocate(sizeof(T));
		return new T[1]{ std::forward<Args...>(args)... };
	}

	template <typename T, typename ... Args>
	T* NewArray(size_t count, Args&&... args)
	{
		char* mem = Memory::Allocate(sizeof(T) * count);
		return new T[count](std::forward<Args...>(args)...);
	}

	template <typename T>
	void Delete(T* obj)
	{
		Memory::Deallocate(obj);
		delete[] obj;
	}


}