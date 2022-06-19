#pragma once

#include "vector.h"

namespace jgr
{

	template<typename T, unsigned COLUMNS, unsigned ROWS, unsigned ALIGNAS = 0>
	class alignas(ALIGNAS) Matrix
	{
	public:
		using ColumnType = Vector<T, ROWS, ALIGNAS>;
		using RowType = Vector<T, COLUMNS, ALIGNAS>;
		using TransposeType = Matrix<T, ROWS, COLUMNS, ALIGNAS>;
		using MatrixType = Matrix<T, COLUMNS, ROWS, ALIGNAS>;

		Matrix() {}

		Matrix(const T(&arr)[COLUMNS * ROWS]);

		const ColumnType& operator[](unsigned int idx) const { return m[idx]; }
		ColumnType& operator[](unsigned int idx) { return m[idx]; }

		RowType Row(unsigned int idx) const;
		ColumnType Column(unsigned int idx) const { return m[idx]; }

		TransposeType Transpose() const;

		static MatrixType Identity();

		T Determinant() const;

		Matrix Inverse() const;

	private:
		ColumnType m[COLUMNS];
	};

	using mat2 = Matrix<float, 2, 2, 4>;
	using mat3 = Matrix<float, 3, 3, 16>;
	using mat4 = Matrix<float, 4, 4, 16>;

	template<typename T, unsigned C, unsigned R, unsigned A>
	Matrix<T, C, R, A>::Matrix(const T(&arr)[C * R])
	{
		for (size_t i = 0; i < C; ++i)
		{
			for (size_t j = 0; j < R; ++j)
			{
				m[i][j] = arr[i * R + j];
			}
		}
	}

	// In the future we can make a magical view thing but not now
	template<typename T, unsigned C, unsigned R, unsigned A>
	typename Matrix<T, C, R, A>::RowType Matrix<T, C, R, A>::Row(unsigned int idx) const
	{
		RowType rowVec;
		for (unsigned c = 0; c < C; ++c)
		{
			rowVec[c] = m[c][idx];
		}

		return rowVec;
	}

	template<typename T, unsigned U, unsigned V, unsigned A>
	Matrix<T, V, U, A> Matrix<T, U, V, A>::Transpose() const
	{
		Matrix<T, V, U, A> ret;

		for (unsigned u = 0; u < U; u++)
		{
			ret[u] = Row(u);
		}

		return ret;
	}
	
	template<>
	inline mat4 mat4::Inverse() const
	{
		mat4 result;
		const float* m_ = reinterpret_cast<const float*>(this);
		float adj[16];

		adj[0] = m_[5] * m_[10] * m_[15] -
			m_[5] * m_[11] * m_[14] -
			m_[9] * m_[6] * m_[15] +
			m_[9] * m_[7] * m_[14] +
			m_[13] * m_[6] * m_[11] -
			m_[13] * m_[7] * m_[10];

		adj[4] = -m_[4] * m_[10] * m_[15] +
			m_[4] * m_[11] * m_[14] +
			m_[8] * m_[6] * m_[15] -
			m_[8] * m_[7] * m_[14] -
			m_[12] * m_[6] * m_[11] +
			m_[12] * m_[7] * m_[10];

		adj[8] = m_[4] * m_[9] * m_[15] -
			m_[4] * m_[11] * m_[13] -
			m_[8] * m_[5] * m_[15] +
			m_[8] * m_[7] * m_[13] +
			m_[12] * m_[5] * m_[11] -
			m_[12] * m_[7] * m_[9];

		adj[12] = -m_[4] * m_[9] * m_[14] +
			m_[4] * m_[10] * m_[13] +
			m_[8] * m_[5] * m_[14] -
			m_[8] * m_[6] * m_[13] -
			m_[12] * m_[5] * m_[10] +
			m_[12] * m_[6] * m_[9];

		adj[1] = -m_[1] * m_[10] * m_[15] +
			m_[1] * m_[11] * m_[14] +
			m_[9] * m_[2] * m_[15] -
			m_[9] * m_[3] * m_[14] -
			m_[13] * m_[2] * m_[11] +
			m_[13] * m_[3] * m_[10];

		adj[5] = m_[0] * m_[10] * m_[15] -
			m_[0] * m_[11] * m_[14] -
			m_[8] * m_[2] * m_[15] +
			m_[8] * m_[3] * m_[14] +
			m_[12] * m_[2] * m_[11] -
			m_[12] * m_[3] * m_[10];

		adj[9] = -m_[0] * m_[9] * m_[15] +
			m_[0] * m_[11] * m_[13] +
			m_[8] * m_[1] * m_[15] -
			m_[8] * m_[3] * m_[13] -
			m_[12] * m_[1] * m_[11] +
			m_[12] * m_[3] * m_[9];

		adj[13] = m_[0] * m_[9] * m_[14] -
			m_[0] * m_[10] * m_[13] -
			m_[8] * m_[1] * m_[14] +
			m_[8] * m_[2] * m_[13] +
			m_[12] * m_[1] * m_[10] -
			m_[12] * m_[2] * m_[9];

		adj[2] = m_[1] * m_[6] * m_[15] -
			m_[1] * m_[7] * m_[14] -
			m_[5] * m_[2] * m_[15] +
			m_[5] * m_[3] * m_[14] +
			m_[13] * m_[2] * m_[7] -
			m_[13] * m_[3] * m_[6];

		adj[6] = -m_[0] * m_[6] * m_[15] +
			m_[0] * m_[7] * m_[14] +
			m_[4] * m_[2] * m_[15] -
			m_[4] * m_[3] * m_[14] -
			m_[12] * m_[2] * m_[7] +
			m_[12] * m_[3] * m_[6];

		adj[10] = m_[0] * m_[5] * m_[15] -
			m_[0] * m_[7] * m_[13] -
			m_[4] * m_[1] * m_[15] +
			m_[4] * m_[3] * m_[13] +
			m_[12] * m_[1] * m_[7] -
			m_[12] * m_[3] * m_[5];

		adj[14] = -m_[0] * m_[5] * m_[14] +
			m_[0] * m_[6] * m_[13] +
			m_[4] * m_[1] * m_[14] -
			m_[4] * m_[2] * m_[13] -
			m_[12] * m_[1] * m_[6] +
			m_[12] * m_[2] * m_[5];

		adj[3] = -m_[1] * m_[6] * m_[11] +
			m_[1] * m_[7] * m_[10] +
			m_[5] * m_[2] * m_[11] -
			m_[5] * m_[3] * m_[10] -
			m_[9] * m_[2] * m_[7] +
			m_[9] * m_[3] * m_[6];

		adj[7] = m_[0] * m_[6] * m_[11] -
			m_[0] * m_[7] * m_[10] -
			m_[4] * m_[2] * m_[11] +
			m_[4] * m_[3] * m_[10] +
			m_[8] * m_[2] * m_[7] -
			m_[8] * m_[3] * m_[6];

		adj[11] = -m_[0] * m_[5] * m_[11] +
			m_[0] * m_[7] * m_[9] +
			m_[4] * m_[1] * m_[11] -
			m_[4] * m_[3] * m_[9] -
			m_[8] * m_[1] * m_[7] +
			m_[8] * m_[3] * m_[5];

		adj[15] = m_[0] * m_[5] * m_[10] -
			m_[0] * m_[6] * m_[9] -
			m_[4] * m_[1] * m_[10] +
			m_[4] * m_[2] * m_[9] +
			m_[8] * m_[1] * m_[6] -
			m_[8] * m_[2] * m_[5];

		float det = m_[0] * adj[0] + m_[1] * adj[4] + m_[2] * adj[8] + m_[3] * adj[12];

		if (fabs(det) < FLT_EPSILON)
			return result;

		float* inv_ = reinterpret_cast<float*>(&result);
		float invdet = 1 / det;

		for (int i = 0; i < 16; i++)
		{
			inv_[i] = adj[i] * invdet;
		}

		return result;
	}

	template<>
	inline mat4 mat4::Transpose() const
	{
		mat4 ret = *this;

		__m128* retmm = reinterpret_cast<__m128*>(&ret);

		_MM_TRANSPOSE4_PS(retmm[0], retmm[1], retmm[2], retmm[3]);
		return ret;
	}

	template<typename T, unsigned U, unsigned V, unsigned A>
	Matrix<T, U, V, A> Matrix<T, U, V, A>::Identity()
	{
		static_assert(U == V, "Not a square matrix");

		Matrix<T, U, V, A> result;

		for (unsigned u = 0; u < U; ++u)
		{
			result[u][u] = 1.0f;
		}

		return result;
	}

	template<typename T, unsigned U, unsigned V, unsigned W, unsigned A>
	Matrix<T, W, V, A> operator*(const Matrix<T, U, V, A>& lhs, const Matrix<T, W, U, A>& rhs)
	{
		Matrix<T, W, V, A> result;
		for (unsigned int i = 0; i < W; ++i)
		{
			const auto& row = lhs.Row(i);
			for (unsigned int j = 0; j < V; ++j)
			{
				result[j][i] = Matrix<T, U, V, A>::RowType::Dot(row, rhs.Column(j));
			}
		}

		return result;
	}

	inline mat4 operator*(const mat4& lhs, const mat4& rhs)
	{
		mat4 result;
		mat4 transpose = lhs.Transpose();

		for (unsigned int i = 0; i < 4; ++i)
		{
			const auto& row = lhs.Row(i);
			for (unsigned int j = 0; j < 4; ++j)
			{
				result[j][i] = vec4::Dot(transpose[i], rhs[j]);
			}
		}

		return result;
	}
}
