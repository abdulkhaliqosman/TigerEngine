#pragma once

#include <cmath>
#include <utility>
#include <algorithm>
#include <immintrin.h>

namespace jgr
{
	// TODO: nan safety

	template <typename T>
	constexpr bool constexpr_greater_or_equal(const T& lhs, const T& rhs)
	{
		return lhs >= rhs;
	}

	template<typename T, unsigned U, unsigned A = sizeof(T)>
	class alignas(A) Vector
	{
	public:
		using VectorType = Vector<T, U, A>;
		using DataType = T[U];
		explicit Vector() :m_Data{ 0.0f } {}

		template<unsigned V>
		explicit Vector(T(& arr)[V])
			:m_Data{}
		{
			const auto minCount = U > V ? U : V;
			for (unsigned i = 0; i < minCount; ++i)
			{
				m_Data[i] = arr[i];
			}
		}

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

		static float Dot(const VectorType& lhs, const VectorType& rhs);

		inline float LengthSquared() const { return Dot(*this, *this); }
		inline float Length() const { return std::sqrt(LengthSquared()); }
		inline VectorType Normalized() const;
		inline void Normalize() { *this = Normalized(); }

		static float Angle(const VectorType& lhs, const VectorType& rhs);

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
	using vec4 = Vector<float, 4, 16>;
	using ivec2 = Vector<int, 2>;
	using ivec4 = Vector<int, 4>;

	// negation
	template<typename T, unsigned U, unsigned A>
	Vector<T, U, A> operator-(const Vector<T, U, A>& v)
	{
		Vector<T, U, A> result = v;
		for (auto& t : result)
		{
			t = -t;
		}

		return result;
	}

	// addition
	template<typename T, unsigned U, unsigned A>
	Vector<T, U, A> operator+(const Vector<T, U, A>& lhs, const Vector<T, U, A>& rhs)
	{
		Vector<T, U, A> result;
		for (unsigned i = 0; i < U; ++i)
		{
			result[i] = lhs[i] + rhs[i];
		}

		return result;
	}

	// subtraction
	template<typename T, unsigned U, unsigned A>
	Vector<T, U, A> operator-(const Vector<T, U, A>& lhs, const Vector<T, U, A>& rhs)
	{
		return lhs + -rhs;
	}

	// scalar product
	template<typename T, unsigned U, unsigned A>
	Vector<T, U, A> operator*(float f, const Vector<T, U, A>& v)
	{
		Vector<T, U, A> result = v;
		for (auto& t : result)
		{
			t *= f;
		}

		return result;
	}

	inline Vector<float, 4> operator*(float f, Vector<float, 4>& v)
	{
		Vector<float, 4> result = v;
		for (auto& t : result)
		{
			t *= f;
		}

		return result;
	}

	// scalar division
	template<typename T, unsigned U, unsigned A>
	Vector<T, U, A> operator/(const Vector<T, U, A>& v, float f)
	{
		return 1 / f * v;
	}

	// elementwise product
	template<typename T, unsigned U, unsigned A>
	Vector<T, U, A> operator*(const Vector<T, U, A>& lhs, const Vector<T, U, A>& rhs)
	{
		return Vector<T, U, A>(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2], lhs[3] * rhs[3]);
	}

	inline vec4 operator*(const vec4& lhs, const vec4& rhs)
	{
		__m128 l = { lhs[0], lhs[1], lhs[2], lhs[3] };
		__m128 r = { rhs[0], rhs[1], rhs[2], rhs[3] };

		//__asm
		//{
		//	mm_mul_ps l, r
		//}
		__m128 d = _mm_mul_ps(l, r);
		
		return vec4(d.m128_f32);
	}

	template<typename T, unsigned U, unsigned A>
	float Vector<T, U, A>::Dot(const Vector<T, U, A>& lhs, const Vector<T, U, A>& rhs)
	{
		float result = 0;

		for (unsigned i = 0; i < U; ++i)
		{
			result += lhs[i] * rhs[i];
		}

		return result;
	}

	template<typename T, unsigned U, unsigned A>
	float Vector<T, U, A>::Angle(const Vector<T, U, A>& lhs, const Vector<T, U, A>& rhs)
	{
		return std::acos(Dot(lhs, rhs) / (lhs.Length() * rhs.Length()));
	}

	template<typename T, unsigned U, unsigned A>
	Vector<T, U, A> Vector<T, U, A>::Normalized() const
	{
		return (1 / Length()) * (*this);
	}

	template<typename T, unsigned U, unsigned A>
	Vector<T, U, A> Vector<T, U, A>::Zero()
	{
		Vector<T, U, A> zero;
		for (auto& elem : zero.m_Data)
		{
			elem = 0.0f;
		}
		return zero;
	}

	template<typename T, unsigned U, unsigned A>
	Vector<T, U, A> Vector<T, U, A>::One()
	{
		Vector<T, U, A> one;
		for (auto& elem : one.m_Data)
		{
			elem = 1.0f;
		}
		return one;
	}
}