#pragma once

#include "Mat.hpp"
#include "Vec3.hpp"

namespace numa
{
	template<typename T>
	class Mat<T, 3, 3>
	{
	public:

		using column_type = Vec<T, 3>;

		using column_type_ref = column_type&;
		using column_type_cref = const column_type&;

		using component_type = typename column_type::component_type;

		using component_type_ref = component_type&;
		using component_type_cref = const component_type&;

		using component_type_ptr = component_type*;
		using component_type_cptr = const component_type*;

		// Constructors

		Mat() : columns() {};

		template<typename U>
		Mat(const U& u);

		template<
			typename X0, typename Y0, typename Z0, // column #0
			typename X1, typename Y1, typename Z1, // column #1
			typename X2, typename Y2, typename Z2> // column #2
		Mat(
			const X0& x0, const Y0& y0, const Z0& z0,  // column #0
			const X1& x1, const Y1& y1, const Z1& z1,  // column #1
			const X2& x2, const Y2& y2, const Z2& z2); // column #2

		template<typename X, typename Y, typename Z>
		Mat(
			const Vec<X, 3>& x,  // column #0
			const Vec<Y, 3>& y,  // column #1
			const Vec<Z, 3>& z); // column #2

		// Converting constructors

		template<typename U, int Rows, int Cols>
		Mat(const Mat<U, Rows, Cols>& mat);

		// Operators

		template<typename U>
		Mat<T, 3, 3>& operator+=(const Mat<U, 3, 3>& mat);

		template<typename U>
		Mat<T, 3, 3>& operator-=(const Mat<U, 3, 3>& mat);

		template<typename U>
		Mat<T, 3, 3>& operator*=(const U& u);

		template<typename U>
		Mat<T, 3, 3>& operator/=(const U& u);

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
			return &_00;
		}
		component_type_cptr Data() const
		{
			return &_00;
		}

		union
		{
			struct
			{
				// 1st column (right)
				component_type _00;
				component_type _10;
				component_type _20;

				// 2nd column (up)
				component_type _01;
				component_type _11;
				component_type _21;

				// 3rd column (forward)
				component_type _02;
				component_type _12;
				component_type _22;
			};
			struct
			{
				column_type right;
				column_type up;
				column_type forward;
			};
			struct
			{
				column_type x;
				column_type y;
				column_type z;
			};
			struct
			{
				column_type columns[3];
			};
		};
	};

	// Constructors

	template<typename T>
	template<typename U>
	Mat<T, 3, 3>::Mat(const U& u)
	{
		right = column_type{ u, 0, 0 };
		up = column_type{ 0, u, 0 };
		forward = column_type{ 0, 0, u };
	}

	template<typename T>
	template<
		typename X0, typename Y0, typename Z0,
		typename X1, typename Y1, typename Z1,
		typename X2, typename Y2, typename Z2>
	Mat<T, 3, 3>::Mat(
		const X0& x0, const Y0& y0, const Z0& z0,
		const X1& x1, const Y1& y1, const Z1& z1,
		const X2& x2, const Y2& y2, const Z2& z2)
	{
		this->right = column_type{ x0, y0, z0 };
		this->up = column_type{ x1, y1, z1 };
		this->forward = column_type{ x2, y2, z2 };
	}

	template<typename T>
	template<typename X, typename Y, typename Z>
	Mat<T, 3, 3>::Mat(
		const Vec<X, 3>& x,
		const Vec<Y, 3>& y,
		const Vec<Z, 3>& z)
	{
		this->right = x;
		this->up = y;
		this->forward = z;
	}

	// Converting constructors

	template<typename T>
	template<typename U, int Rows, int Cols>
	Mat<T, 3, 3>::Mat(const Mat<U, Rows, Cols>& mat)
		: Mat(T(1))
	{
		int minColsDim = std::min(3, Cols);
		for (int i = 0; i < minColsDim; i++)
		{
			this->columns[i] = mat[i];
		}
	}

	// Operators

	// 1) Defined in the class

	template<typename T>
	template<typename U>
	Mat<T, 3, 3>& Mat<T, 3, 3>::operator+=(const Mat<U, 3, 3>& mat)
	{
		this->right += mat.right;
		this->up += mat.up;
		this->forward += mat.forward;
		return *this;
	}

	template<typename T>
	template<typename U>
	Mat<T, 3, 3>& Mat<T, 3, 3>::operator-=(const Mat<U, 3, 3>& mat)
	{
		this->right -= mat.right;
		this->up -= mat.up;
		this->forward -= mat.forward;

		return *this;
	}

	template<typename T>
	template<typename U>
	Mat<T, 3, 3>& Mat<T, 3, 3>::operator*=(const U& u)
	{
		this->right *= u;
		this->up *= u;
		this->forward *= u;
		return *this;
	}

	template<typename T>
	template<typename U>
	Mat<T, 3, 3>& Mat<T, 3, 3>::operator/=(const U& u)
	{
		this->right /= u;
		this->up /= u;
		this->forward /= u;
		return *this;
	}

	// 2) Defined as separate functions

	//    ---

	// Common type definitions

	using Mat3 = Mat<float, 3, 3>;
}