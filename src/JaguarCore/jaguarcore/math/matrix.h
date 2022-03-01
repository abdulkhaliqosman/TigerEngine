#pragma once

#include "vector.h"

namespace jgr
{

	template<typename T, unsigned COLUMNS, unsigned ROWS>
	class Matrix
	{
	public:
		using ColumnType = Vector<T, ROWS>;
		using RowType = Vector<T, COLUMNS>;
		using TransposeType = Matrix<T, ROWS, COLUMNS>;
		using MatrixType = Matrix<T, COLUMNS, ROWS>;

		Matrix() {}

		Matrix(const T(&arr)[COLUMNS * ROWS]);

		const ColumnType& operator[](unsigned int idx) const { return m[idx]; }
		ColumnType& operator[](unsigned int idx) { return m[idx]; }

		RowType Row(unsigned int idx) const;
		ColumnType Column(unsigned int idx) const { return m[idx]; }

		TransposeType Transpose() const;

		static MatrixType Identity();



	private:
		ColumnType m[COLUMNS];
	};

	using mat4 = Matrix<float, 4, 4>;

	template<typename T, unsigned C, unsigned R>
	Matrix<T, C, R>::Matrix(const T(&arr)[C * R])
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
	template<typename T, unsigned COLUMNS, unsigned ROWS>
	typename Matrix<T, COLUMNS, ROWS>::RowType Matrix<T, COLUMNS, ROWS>::Row(unsigned int idx) const
	{
		RowType rowVec;
		for (unsigned c = 0; c < COLUMNS; ++c)
		{
			rowVec[c] = m[c][idx];
		}

		return rowVec;
	}

	template<typename T, unsigned U, unsigned V>
	Matrix<T, V, U> Matrix<T, U, V>::Transpose() const
	{
		Matrix<T, V, U> ret;

		for (unsigned u = 0; u < U; u++)
		{
			ret[u] = Row(u);
		}

		return ret;
	}

	template<typename T, unsigned U, unsigned V>
	Matrix<T, U, V> Matrix<T, U, V>::Identity()
	{
		static_assert(U == V, "Not a square matrix");

		Matrix<T, U, V> result;

		for (unsigned u = 0; u < U; ++u)
		{
			result[u][u] = 1.0f;
		}

		return result;
	}

	template<typename T, unsigned U, unsigned V, unsigned W>
	Matrix<T, W, V> operator*(const Matrix<T, U, V>& lhs, const Matrix<T, W, U>& rhs)
	{
		Matrix<T, W, V> result;
		for (unsigned int i = 0; i < W; ++i)
		{
			const auto& row = lhs.Row(i);
			for (unsigned int j = 0; j < V; ++j)
			{
				result[j][i] = vec4::Dot(row, rhs.Column(j));
			}
		}

		return result;
	}
}
