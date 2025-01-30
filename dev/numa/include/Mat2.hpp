#pragma once

#include "Mat.hpp"
#include "Vec2.hpp"

namespace numa
{
	template<typename T>
	class Mat<T, 2, 2>
	{
	public:

		using column_type = Vec<T, 2>;

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

		template<
			typename X0, typename Y0, // column #0
			typename X1, typename Y1> // column #1
		Mat(
			const X0& x0, const Y0& y0,  // column #0
			const X1& x1, const Y1& y1); // column #1

		// Converting constructors

		template<typename U, int Rows, int Cols>
		Mat(const Mat<U, Rows, Cols>& mat);

		// Operators

		template<typename U>
		Mat<T, 2, 2>& operator+=(const Mat<U, 2, 2>& mat);

		template<typename U>
		Mat<T, 2, 2>& operator-=(const Mat<U, 2, 2>& mat);

		template<typename U>
		Mat<T, 2, 2>& operator*=(const U& u);

		template<typename U>
		Mat<T, 2, 2>& operator/=(const U& u);

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
			// return columns[0].Data();
			// return right.Data();
			return &_00;
		}
		component_type_cptr Data() const
		{
			// return columns[0].Data();
			// return right.Data();
			return &_00;
		}

		union
		{
			struct
			{
				// 1st column (right)
				component_type _00;
				component_type _10;

				// 2nd column (up)
				component_type _01;
				component_type _11;
			};
			struct
			{
				column_type right;
				column_type up;
			};
			struct
			{
				column_type columns[2];
			};
		};

	};

	// Constructors

	template<typename T>
	template<typename U>
	Mat<T, 2, 2>::Mat(const U& u)
	{
		// Other elements won't be initialized,
		// containing "garbage" data instead.
		// _00 = _11 = static_cast<T>(u);

		right = column_type{ static_cast<T>(u), T(0) };
		up = column_type{ T(0), static_cast<T>(u) };
	}

	template<typename T>
	template<
		typename X0, typename Y0,
		typename X1, typename Y1>
	Mat<T, 2, 2>::Mat(
		const X0& x0, const Y0& y0,
		const X1& x1, const Y1& y1)
	{
		// _00 = x0;
		// _10 = y0;

		// _01 = x1;
		// _11 = y1;

		this->right = column_type{ x0, y0 };
		this->up    = column_type{ x1, y1 };
	}

	// Converting constructors

	template<typename T>
	template<typename U, int Rows, int Cols>
	Mat<T, 2, 2>::Mat(const Mat<U, Rows, Cols>& mat)
	{
		// int minRowsDim = std::min(2, Rows);
		int minColsDim = std::min(2, Cols);
		for (int i = 0; i < minColsDim; i++)
		{
			// for (int j = 0; j < minRowsDim; j++)
			// {
				// this->columns[j] = static_cast<T>(mat[i][j]); // same as below
			// }
			this->columns[i] = mat[i];
		}
	}

	// Operators

	// 1) Defined in the class

	template<typename T>
	template<typename U>
	Mat<T, 2, 2>& Mat<T, 2, 2>::operator+=(const Mat<U, 2, 2>& mat)
	{
		// this->right += mat[0];
		// this->up += mat[1];

		this->right += mat.right;
		this->up += mat.up;

		return *this;
	}

	template<typename T>
	template<typename U>
	Mat<T, 2, 2>& Mat<T, 2, 2>::operator-=(const Mat<U, 2, 2>& mat)
	{
		// this->right -= mat[0];
		// this->up -= mat[1];

		this->right -= mat.right;
		this->up -= mat.up;

		return *this;
	}

	template<typename T>
	template<typename U>
	Mat<T, 2, 2>& Mat<T, 2, 2>::operator*=(const U& u)
	{
		this->right *= u;
		this->up *= u;

		return *this;
	}

	template<typename T>
	template<typename U>
	Mat<T, 2, 2>& Mat<T, 2, 2>::operator/=(const U& u)
	{
		this->right /= u;
		this->up /= u;

		return *this;
	}

	// 2) Defined as separate functions
	
	//    ---

	// Common type definitions

	using Mat2 = Mat<float, 2, 2>;
}