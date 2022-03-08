#pragma once

#include <cmath>
#include <utility>
#include <algorithm>

namespace jgr
{
	// TODO: nan safety

	template <typename T>
	constexpr bool constexpr_greater_or_equal(const T& lhs, const T& rhs)
	{
		return lhs >= rhs;
	}

	template<typename T, unsigned U>
	class Vector
	{
	public:
		using VectorType = Vector<T, U>;
		using DataType = T[U];
		explicit Vector() :m_Data{ 0.0f } {}

		template<unsigned V>
		explicit Vector(const T(&arr)[V])
			:m_Data{}
		{
			const auto minCount = U > V ? U : V;
			for (unsigned i = 0; i < minCount; ++i)
			{
				m_Data[i] = arr[i];
			}
		}

		template<unsigned V>
		explicit Vector(Vector<T, V>& vec)
			:m_Data{}
		{
			const auto minCount = U > V ? U : V;
			for (unsigned i = 0; i < minCount; ++i)
			{
				m_Data[i] = vec[i];
			}
		}

		template<unsigned V>
		explicit Vector(const Vector<T, V>& vec)
			:m_Data{}
		{
			const auto minCount = U > V ? U : V;
			for (unsigned i = 0; i < minCount; ++i)
			{
				m_Data[i] = vec[i];
			}
		}

		template<unsigned V>
		explicit Vector(Vector<T, V>&& vec)
			:m_Data{}
		{
			const auto minCount = U > V ? U : V;
			for (unsigned i = 0; i < minCount; ++i)
			{
				m_Data[i] = vec[i];
			}
		}

		template<typename ... Args>
		explicit Vector(Args&& ... args) :m_Data{ std::forward<Args>(args)... } {}

		template<typename = typename std::enable_if<constexpr_greater_or_equal(U, 1u)>::type>
		T x() const { return m_Data[0]; }

		template<typename = typename std::enable_if<constexpr_greater_or_equal(U, 1u)>::type>
		T& x() { return m_Data[0]; }

		template<typename = typename std::enable_if<constexpr_greater_or_equal(U, 2u)>::type>
		T y() const { return m_Data[1]; }

		template<typename = typename std::enable_if<constexpr_greater_or_equal(U, 2u)>::type>
		T& y() { return m_Data[1]; }

		template<typename = typename std::enable_if<constexpr_greater_or_equal(U, 3u)>::type>
		T z() const { return m_Data[2]; }

		template<typename = typename std::enable_if<constexpr_greater_or_equal(U, 3u)>::type>
		T& z() { return m_Data[2]; }

		template<typename = typename std::enable_if<constexpr_greater_or_equal(U, 4u)>::type>
		T w() const { return m_Data[3]; }

		template<typename = typename std::enable_if<constexpr_greater_or_equal(U, 4u)>::type>
		T& w() { return m_Data[3]; }

		inline T operator[](unsigned int i) const { return m_Data[i]; }
		inline T& operator[](unsigned int i) { return m_Data[i]; }

		static float Dot(const Vector<T, U>& lhs, const Vector<T, U>& rhs);

		inline float LengthSquared() const { return Dot(*this, *this); }
		inline float Length() const { return std::sqrt(LengthSquared()); }
		inline VectorType Normalized() const;
		inline void Normalize() { *this = Normalized(); }

		static float Angle(const Vector<T, U>& lhs, const Vector<T, U>& rhs);

		static VectorType Right() { return VectorType{ 1.0f, 0.0f }; };
		static VectorType Left() { return -Right(); };

		template<typename = typename std::enable_if<constexpr_greater_or_equal(U, 2u)>::type>
		static VectorType Up() { return VectorType{ 0.0f, 1.0f }; }

		template<typename = typename std::enable_if<constexpr_greater_or_equal(U, 2u)>::type>
		static VectorType Down() { return -Up(); };

		template<typename = typename std::enable_if<constexpr_greater_or_equal(U, 3u)>::type>
		static VectorType Forward() { return VectorType{ 0.0f, 0.0f, 1.0f }; }

		template<typename = typename std::enable_if<constexpr_greater_or_equal(U, 3u)>::type>
		static VectorType Back() { return -Forward(); };

		static VectorType Zero();
		static VectorType One();

		T* begin() { return m_Data; }
		T* end() { return m_Data + U; }

		inline DataType& Data() { return m_Data; }
		inline const DataType& Data() const { return m_Data; }
	private:
		T m_Data[U];
	};

	using vec2 = Vector<float, 2>;
	using vec3 = Vector<float, 3>;
	using vec4 = Vector<float, 4>;
	using ivec2 = Vector<int, 2>;
	using ivec4 = Vector<int, 4>;

	// negation
	template<typename T, unsigned U>
	Vector<T, U> operator-(const Vector<T, U>& v)
	{
		Vector<T, U> result = v;
		for (auto& t : result)
		{
			t = -t;
		}

		return result;
	}

	// addition
	template<typename T, unsigned U>
	Vector<T, U> operator+(const Vector<T, U>& lhs, const Vector<T, U>& rhs)
	{
		Vector<T, U> result;
		for (unsigned i = 0; i < U; ++i)
		{
			result[i] = lhs[i] + rhs[i];
		}

		return result;
	}

	// subtraction
	template<typename T, unsigned U>
	Vector<T, U> operator-(const Vector<T, U>& lhs, const Vector<T, U>& rhs)
	{
		return lhs + -rhs;
	}

	// scalar product
	template<typename T, unsigned U>
	Vector<T, U> operator*(float f, const Vector<T, U>& v)
	{
		Vector<T, U> result = v;
		for (auto& t : result)
		{
			t *= f;
		}

		return result;
	}

	// scalar division
	template<typename T, unsigned U>
	Vector<T, U> operator/(const Vector<T, U>& v, float f)
	{
		return 1 / f * v;
	}

	// elementwise product
	template<typename T, unsigned U>
	Vector<T, U> operator*(const Vector<T, U>& lhs, const Vector<T, U>& rhs)
	{
		return Vector<T, U>(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2], lhs[3] * rhs[3]);
	}

	template<typename T, unsigned U>
	float Vector<T, U>::Dot(const Vector<T, U>& lhs, const Vector<T, U>& rhs)
	{
		return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2] + lhs[3] * rhs[3];
	}

	template<typename T, unsigned U>
	float Vector<T, U>::Angle(const Vector<T, U>& lhs, const Vector<T, U>& rhs)
	{
		return std::acos(Dot(lhs, rhs) / (lhs.Length() * rhs.Length()));
	}

	template<typename T, unsigned U>
	Vector<T, U> Vector<T, U>::Normalized() const
	{
		return (1 / Length()) * (*this);
	}

	template<typename T, unsigned U>
	Vector<T, U> Vector<T, U>::Zero()
	{
		Vector<T, U> zero;
		for (auto& elem : zero.m_Data)
		{
			elem = 1.0f;
		}
		return zero;
	}

	template<typename T, unsigned U>
	Vector<T, U> Vector<T, U>::One()
	{
		Vector<T, U> one;
		for (auto& elem : one.m_Data)
		{
			elem = 1.0f;
		}
		return one;
	}
}