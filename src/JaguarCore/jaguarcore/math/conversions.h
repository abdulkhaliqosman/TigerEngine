#pragma once

namespace jgr
{
	namespace Math
	{
		template<typename T>
		T DegToRad(T deg)
		{
			return deg * 3.14159265 / 180.0;
		}

		template<typename T>
		T RadToDeg(T rad)
		{
			return rad * 180.0 / 3.14159265;
		}
	}
}

