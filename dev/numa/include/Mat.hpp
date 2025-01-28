#pragma once

#include "Vec.hpp"

#include <algorithm>
// #include <cassert>
// #include <type_traits>

namespace numa
{
	template<typename T, int Rows, int Cols>
	class Mat
	{
	public:

		using column_type = Vec<T, Rows>;

		using column_type_ref = column_type&;
		using column_type_cref = const column_type&;

		using component_type = typename column_type::component_type;

		using component_type_ref = component_type&;
		using component_type_cref = const component_type&;

		using component_type_ptr = component_type*;
		using component_type_cptr = const component_type*;

		// Constructors

		Mat() = default;

		template<typename U>
		Mat(const U& u);

		template<typename U, int Rows2, int Cols2>
		Mat(const Mat<U, Rows2, Cols2>& mat);

		// Operators

		template<typename U>
		Mat<T, Rows, Cols>& operator+=(const Mat<U, Rows, Cols>& mat);

		template<typename U>
		Mat<T, Rows, Cols>& operator-=(const Mat<U, Rows, Cols>& mat);

		template<typename U>
		Mat<T, Rows, Cols>& operator*=(const U& u);

		template<typename U>
		Mat<T, Rows, Cols>& operator/=(const U& u);

		column_type_ref& operator[](int idx)
		{
			return columns[idx];
		}
		column_type_cref& operator[](int idx) const
		{
			return columns[idx];
		}

		component_type_ptr Data()
		{
			return columns[0].Data();
		}
		component_type_cptr Data() const
		{
			return columns[0].Data();
		}

	private:

		column_type columns[Cols];
	};

	// Constructors

	template<typename T, int Rows, int Cols>
	template<typename U>
	Mat<T, Rows, Cols>::Mat(const U& u)
	{
		for (int col = 0; col < Cols; col++)
		{
			columns[col] = column_type{ u };
		}
	}

	// Converting constructors

	template<typename T, int Rows, int Cols>
	template<typename U, int Rows2, int Cols2>
	Mat<T, Rows, Cols>::Mat(const Mat<U, Rows2, Cols2>& mat)
	{
		int minRowsDim = std::min(Rows, Rows2);
		int minColsDim = std::min(Cols, Cols2);
		for (int i = 0; i < minColsDim; i++)
		{
			for (int j = 0; j < minRowsDim; j++)
			{
				this->columns[j] = static_cast<T>(mat[i][j]); // same as below
			}
		}
	}

	// Operators

	// 1) Defined in the class

	template<typename T, int Rows, int Cols>
	template<typename U>
	Mat<T, Rows, Cols>& Mat<T, Rows, Cols>::operator+=(const Mat<U, Rows, Cols>& mat)
	{
		for (int i = 0; i < Cols; i++)
		{
			this->columns[i] += mat[i];
		}
		return *this;
	}

	template<typename T, int Rows, int Cols>
	template<typename U>
	Mat<T, Rows, Cols>& Mat<T, Rows, Cols>::operator-=(const Mat<U, Rows, Cols>& mat)
	{
		for (int i = 0; i < Cols; i++)
		{
			this->columns[i] -= mat[i];
		}
		return *this;
	}

	template<typename T, int Rows, int Cols>
	template<typename U>
	Mat<T, Rows, Cols>& Mat<T, Rows, Cols>::operator*=(const U& u)
	{
		for (int i = 0; i < Cols; i++)
		{
			this->columns[i] *= static_cast<T>(u);
		}
		return *this;
	}

	template<typename T, int Rows, int Cols>
	template<typename U>
	Mat<T, Rows, Cols>& Mat<T, Rows, Cols>::operator/=(const U& u)
	{
		for (int i = 0; i < Cols; i++)
		{
			this->columns[i] /= static_cast<T>(u);
		}
		return *this;
	}

	// 2) Defined as separate functions

	// The `VecRows` template parameter is unnecessary.
	// We can reuse the `MatCols` parameter for that.
	// This way we can also avoid having to use the `std::enable_if` check
	// in order to prevent multiplications when the column size of a matrix
	// doesn't match the rows size of a vector.
	/*
	template<typename T, int MatRows, int MatCols, int VecRows,
		std::enable_if_t<MatCols == VecRows, bool> = true>
	Vec<T, MatRows> operator*(const Mat<T, MatRows, MatCols>& m, const Vec<T, VecRows>& v)
	{
		// assert(MatCols == VecRows && "The matrix column size doesn't match the vector row size!");

		Vec<T, MatRows> res{ T(0) };
		for (int i = 0; i < MatCols; i++)
		{
			res += m[i] * v[i];
		}
		return res;
	}
	*/

	template<typename T, typename U, int Rows, int Cols>
	Mat<T, Rows, Cols> operator+(const Mat<T, Rows, Cols>& m1, const Mat<U, Rows, Cols>& m2)
	{
		Mat<T, Rows, Cols> res{};
		for (int i = 0; i < Cols; i++)
		{
			res[i] = m1[i] + m2[i];
		}
		return res;
	}

	template<typename T, typename U, int Rows, int Cols>
	Mat<T, Rows, Cols> operator-(const Mat<T, Rows, Cols>& m1, const Mat<U, Rows, Cols>& m2)
	{
		Mat<T, Rows, Cols> res{};
		for (int i = 0; i < Cols; i++)
		{
			res[i] = m1[i] + m2[i];
		}
		return res;
	}

	template<typename T, typename U, int Rows, int Cols>
	Mat<T, Rows, Cols> operator*(const Mat<T, Rows, Cols>& m, const U& u)
	{
		Mat<T, Rows, Cols> res{};
		for (int i = 0; i < Cols; i++)
		{
			res[i] = m[i] * static_cast<T>(u);
		}
		return res;
	}

	template<typename T, typename U, int Rows, int Cols>
	Mat<T, Rows, Cols> operator*(const U& u, const Mat<T, Rows, Cols>& m)
	{
		Mat<T, Rows, Cols> res{};
		for (int i = 0; i < Cols; i++)
		{
			res[i] = static_cast<T>(u) * m[i];
		}
		return res;
	}

	template<typename T, typename U, int Rows, int Cols>
	Vec<T, Rows> operator*(const Mat<T, Rows, Cols>& m, const Vec<U, Cols>& v)
	{
		Vec<T, Rows> res{ T(0) };
		for (int i = 0; i < Cols; i++)
		{
			res[i] = m[i] * v[i];
		}
		return res;
	}

	template<typename T, typename U, int Rows, int Cols>
	Mat<T, Rows, Cols> operator/(const Mat<T, Rows, Cols>& m, const U& u)
	{
		Mat<T, Rows, Cols> res{};
		for (int i = 0; i < Cols; i++)
		{
			res[i] = m[i] / static_cast<T>(u);
		}
		return res;
	}
}