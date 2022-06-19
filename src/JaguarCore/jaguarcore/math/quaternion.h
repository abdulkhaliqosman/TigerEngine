#pragma once

#include "jaguarcore/math/math.h"

namespace jgr
{
	struct EulerAngles
	{
		float pitch = 0.0f;
		float yaw = 0.0f;
		float roll = 0.0f;
	};

	template<typename T, unsigned U>
	class Quaternion : public Vector<T, 4, U>
	{
	public:
		using BaseType = Vector<T, 4, U>;

		template<typename ... Args>
		explicit Quaternion(Args&& ... args) :BaseType(std::forward<Args>(args)...) {}

		inline static Quaternion Identity() { return Quaternion{ 0.0f,0.0f,0.0f,1.0f }; }

		inline Quaternion Conjugate() const { return Quaternion{ -BaseType::x(), -BaseType::y(), -BaseType::z(), BaseType::w() }; }

		float NormSquared() const { return ((*this) * Conjugate()).w(); }
		inline float Norm() const { return sqrt(NormSquared()); }
		inline Quaternion Inverse() const { return Quaternion{ Conjugate() / NormSquared() }; }

		static Quaternion AngleAxis(float angle, const BaseType& axis)
		{
			BaseType norm = axis.Normalized();
			float s = sinf(angle * 0.5f);
			return Quaternion(norm.x() * s, norm.y() * s, norm.z() * s, cosf(angle * 0.5f));
		}

		static Quaternion FromEulerAngles(const EulerAngles& eulerAngles)
		{
			Quaternion pitch = AngleAxis(Math::DegToRad(eulerAngles.pitch), BaseType::Right());
			Quaternion yaw = AngleAxis(Math::DegToRad(eulerAngles.yaw), BaseType::Up());
			Quaternion roll = AngleAxis(Math::DegToRad(eulerAngles.roll), BaseType::Forward());

			// yaw then pitch finally roll
			return roll * pitch * yaw;
		}


	};

	using quat = Quaternion<float, 16>;
	
	template<typename T, unsigned U>
	Quaternion<T, U> operator*(const Quaternion<T, U>& lhs, const Quaternion<T, U>& rhs)
	{
		return Quaternion<T, U>{
			lhs.w() * rhs.x() + lhs.x() * rhs.w() + lhs.y() * rhs.z() - lhs.z() * rhs.y(),
			lhs.w() * rhs.y() + lhs.y() * rhs.w() + lhs.z() * rhs.x() - lhs.x() * rhs.z(),
			lhs.w() * rhs.z() + lhs.z() * rhs.w() + lhs.x() * rhs.y() - lhs.y() * rhs.x(),
			lhs.w() * rhs.w() - lhs.x() * rhs.x() - lhs.y() * rhs.y() - lhs.z() * rhs.z()
		};
	}

	template<typename T, unsigned U>
	Vector<T, 4, U> operator*(const Quaternion<T, U>& q, const Vector<T, 4, U>& v)
	{
		Quaternion<T, U> vq{ v.x(), v.y(), v.z() };

		Quaternion<T, U> result = q * vq * q.Conjugate();

		return Vector<T, 4, U>(result.x(), result.y(), result.z());
	}

	template<typename T, unsigned U>
	Quaternion<T, U> operator+(const Quaternion<T, U>& lhs, const Quaternion<T, U>& rhs)
	{
		return Quaternion<T, U>(Vector<T, 4, U>(lhs.Data()) + Vector<T, 4, U>(rhs.Data()));
	}

	template<typename T, unsigned U>
	Quaternion<T, U> operator*(float f, const Quaternion<T, U>& rhs)
	{
		return Quaternion<T, U>(f * Vector<T, 4, U>(rhs.Data()));
	}

	template<typename T, unsigned U>
	Quaternion<T, U> operator-(const Quaternion<T, U>& q)
	{
		return Quaternion<T, U>(-Vector<T, 4, U>(q.Data()));
	}

}