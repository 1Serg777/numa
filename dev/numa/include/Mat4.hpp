#pragma once

#include "Mat.hpp"
#include "Vec4.hpp"

namespace numa
{
	template<typename T>
	class Mat<T, 4, 4>
	{
	public:

		using column_type = Vec<T, 4>;

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
			typename X0, typename Y0, typename Z0, typename W0, // column #0
			typename X1, typename Y1, typename Z1, typename W1, // column #1
			typename X2, typename Y2, typename Z2, typename W2, // column #2
			typename X3, typename Y3, typename Z3, typename W3> // column #3
		Mat(
			const X0& x0, const Y0& y0, const Z0& z0, const W0& w0,  // column #0
			const X1& x1, const Y1& y1, const Z1& z1, const W1& w1,  // column #1
			const X2& x2, const Y2& y2, const Z2& z2, const W2& w2,  // column #2
			const X3& x3, const Y3& y3, const Z3& z3, const W3& w3); // column #3

		template<typename X, typename Y, typename Z, typename W>
		Mat(
			const Vec<X, 4>& x,  // column #0
			const Vec<Y, 4>& y,  // column #1
			const Vec<Z, 4>& z,  // column #2
			const Vec<W, 4>& w); // column #3

		// Converting constructors

		template<typename U, int Rows, int Cols>
		Mat(const Mat<U, Rows, Cols>& mat);

		// Operators

		template<typename U>
		Mat<T, 4, 4>& operator+=(const Mat<U, 4, 4>& mat);

		template<typename U>
		Mat<T, 4, 4>& operator-=(const Mat<U, 4, 4>& mat);

		template<typename U>
		Mat<T, 4, 4>& operator*=(const U& u);

		template<typename U>
		Mat<T, 4, 4>& operator/=(const U& u);

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
				component_type _30;

				// 2nd column (up)
				component_type _01;
				component_type _11;
				component_type _21;
				component_type _31;

				// 3rd column (forward)
				component_type _02;
				component_type _12;
				component_type _22;
				component_type _32;

				// 4rd column (translation)
				component_type _03;
				component_type _13;
				component_type _23;
				component_type _33;
			};
			struct
			{
				column_type right;
				column_type up;
				column_type forward;
				column_type translation;
			};
			struct
			{
				column_type x;
				column_type y;
				column_type z;
				column_type w;
			};
			struct
			{
				column_type columns[4];
			};
		};
	};

	// Constructors

	template<typename T>
	template<typename U>
	Mat<T, 4, 4>::Mat(const U& u)
	{
		right = column_type{ u, 0, 0, 0 };
		up = column_type{ 0, u, 0, 0 };
		forward = column_type{ 0, 0, u, 0 };
		translation = column_type{ 0, 0, 0, u };
	}

	template<typename T>
	template<
		typename X0, typename Y0, typename Z0, typename W0,
		typename X1, typename Y1, typename Z1, typename W1,
		typename X2, typename Y2, typename Z2, typename W2,
		typename X3, typename Y3, typename Z3, typename W3>
	Mat<T, 4, 4>::Mat(
		const X0& x0, const Y0& y0, const Z0& z0, const W0& w0,
		const X1& x1, const Y1& y1, const Z1& z1, const W1& w1,
		const X2& x2, const Y2& y2, const Z2& z2, const W2& w2,
		const X3& x3, const Y3& y3, const Z3& z3, const W3& w3)
	{
		this->right = column_type{ x0, y0, z0, w0 };
		this->up = column_type{ x1, y1, z1, w1 };
		this->forward = column_type{ x2, y2, z2, w2 };
		this->translation = column_type{ x3, y3, z3, w3 };
	}

	template<typename T>
	template<typename X, typename Y, typename Z, typename W>
	Mat<T, 4, 4>::Mat(
		const Vec<X, 4>& x,
		const Vec<Y, 4>& y,
		const Vec<Z, 4>& z,
		const Vec<W, 4>& w)
	{
		this->right = x;
		this->up = y;
		this->forward = z;
		this->translation = w;
	}

	// Converting constructors

	template<typename T>
	template<typename U, int Rows, int Cols>
	Mat<T, 4, 4>::Mat(const Mat<U, Rows, Cols>& mat)
		: components()
	{
		int minColsDim = std::min(4, Cols);
		for (int i = 0; i < minColsDim; i++)
		{
			this->columns[i] = mat[i];
		}
	}

	// Operators

	// 1) Defined in the class

	template<typename T>
	template<typename U>
	Mat<T, 4, 4>& Mat<T, 4, 4>::operator+=(const Mat<U, 4, 4>& mat)
	{
		this->right += mat.right;
		this->up += mat.up;
		this->forward += mat.forward;
		this->translation += mat.translation;
		return *this;
	}

	template<typename T>
	template<typename U>
	Mat<T, 4, 4>& Mat<T, 4, 4>::operator-=(const Mat<U, 4, 4>& mat)
	{
		this->right -= mat.right;
		this->up -= mat.up;
		this->forward -= mat.forward;
		this->translation -= mat.translation;
		return *this;
	}

	template<typename T>
	template<typename U>
	Mat<T, 4, 4>& Mat<T, 4, 4>::operator*=(const U& u)
	{
		this->right *= u;
		this->up *= u;
		this->forward *= u;
		this->translation *= u;
		return *this;
	}

	template<typename T>
	template<typename U>
	Mat<T, 4, 4>& Mat<T, 4, 4>::operator/=(const U& u)
	{
		this->right /= u;
		this->up /= u;
		this->forward /= u;
		this->translation /= u;
		return *this;
	}

	// 2) Defined as separate functions

	//    ---

	// Common type definitions

	using Mat4 = Mat<float, 4, 4>;
}