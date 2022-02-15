#pragma once

#include <utility>

namespace jgr
{
	template <typename T, typename ... Args>
	T* New(Args&&... args)
	{
		return new T(std::forward<Args...>(args)...);
	}

	template <typename T>
	void Delete(T* obj)
	{
		delete obj;
	}
}