#pragma once

#include "Vec.hpp"

#include <algorithm>
#include <type_traits>

namespace numa {

	template<typename T, int Rows, int Cols>
	class Mat {
	public:
		using column_type = Vec<T, Rows>;
		using row_type = Vec<T, Cols>;

		using column_type_ref = column_type&;
		using column_type_cref = const column_type&;

		using column_type_ptr = column_type*;
		using column_type_cptr = const column_type*;

		using row_type_ref = row_type&;
		using row_type_cref = const row_type&;

		using row_type_ptr = row_type*;
		using row_type_cptr = const row_type*;

		using component_type = typename column_type::component_type;

		using component_type_ref = component_type&;
		using component_type_cref = const component_type&;

		using component_type_ptr = component_type*;
		using component_type_cptr = const component_type*;

		// Constructors

		Mat() : columns() {};
		template<typename U>
		Mat(const U& u) {
			int minDim = std::min(Cols, Rows);
			for (int i = 0; i < minDim; i++) {
				columns[i][i] = static_cast<T>(u);
			}
		}

		// Converting constructors

		template<typename U, int Rows2, int Cols2>
		Mat(const Mat<U, Rows2, Cols2>& mat)
			: Mat(T(1)) {
			int minCols = std::min(Cols, Cols2);
			int minRows = std::min(Rows, Rows2);
			for (int i = 0; i < minCols; i++) {
				for (int j = 0; j < minRows; j++) {
					columns[i][j] = static_cast<T>(m[i][j]);
				}
			}
		}

		// Operators

		template<typename U>
		Mat<T, Rows, Cols>& operator+=(const U& u) {
			for (int i = 0; i < Cols; i++) {
				this->columns[i] += u;
			}
			return *this;
		}
		template<typename U>
		Mat<T, Rows, Cols>& operator+=(const Mat<U, Rows, Cols>& mat) {
			for (int i = 0; i < Cols; i++) {
				this->columns[i] += mat[i];
			}
			return *this;
		}

		template<typename U>
		Mat<T, Rows, Cols>& operator-=(const U& u) {
			for (int i = 0; i < Cols; i++) {
				this->columns[i] -= u;
			}
			return *this;
		}
		template<typename U>
		Mat<T, Rows, Cols>& operator-=(const Mat<U, Rows, Cols>& mat) {
			for (int i = 0; i < Cols; i++) {
				this->columns[i] -= mat[i];
			}
			return *this;
		}

		template<typename U>
		Mat<T, Rows, Cols>& operator*=(const U& u) {
			for (int i = 0; i < Cols; i++) {
				this->columns[i] *= u;
			}
			return *this;
		}

		template<typename U>
		Mat<T, Rows, Cols>& operator/=(const U& u) {
			for (int i = 0; i < Cols; i++) {
				this->columns[i] /= u;
			}
			return *this;
		}
		template<typename U>
		Mat<T, Rows, Cols>& operator/=(const Mat<U, Rows, Cols>& mat) {
			for (int i = 0; i < Cols; i++) {
				this->columns[i] /= mat[i];
			}
			return *this;
		}

		column_type_ref& operator[](int idx) {
			return columns[idx];
		}
		column_type_cref& operator[](int idx) const {
			return columns[idx];
		}

		component_type_ptr Data() {
			return columns[0].Data();
		}
		component_type_cptr Data() const {
			return columns[0].Data();
		}

	private:
		column_type columns[Cols];
	};

	// Mat2 specialization

	template<typename T>
	class Mat<T, 2, 2> {
	public:
		using column_type = Vec<T, 2>;
		using row_type = Vec<T, 2>;

		using column_type_ref = column_type&;
		using column_type_cref = const column_type&;

		using column_type_ptr = column_type*;
		using column_type_cptr = const column_type*;

		using row_type_ref = row_type&;
		using row_type_cref = const row_type&;

		using row_type_ptr = row_type*;
		using row_type_cptr = const row_type*;

		using component_type = typename column_type::component_type;

		using component_type_ref = component_type&;
		using component_type_cref = const component_type&;

		using component_type_ptr = component_type*;
		using component_type_cptr = const component_type*;

		// Constructors

		Mat() : columns() {};
		template<typename U>
		Mat(const U& u) {
			x = column_type{u, 0};
			y = column_type{0, u};
		}

		template<typename X0, typename Y0, // column #0 types
			     typename X1, typename Y1> // column #1 types
		Mat(const X0& x0, const Y0& y0,    // column #0
			const X1& x1, const Y1& y1) {  // column #1
			this->x = column_type{x0, y0};
			this->y = column_type{x1, y1};
		}

		template<typename X,      // column #0 type
			     typename Y>      // column #1 type
		Mat(const Vec<X, 2>& x,   // column #0
			const Vec<Y, 2>& y) { // column #1
			this->x = x;
			this->y = y;
		}

		// Converting constructors

		template<typename U>
		Mat(const Mat<U, 2, 2>& m) {
			this->x = m.x;
			this->y = m.y;
		}
		template<typename U>
		Mat(const Mat<U, 3, 3>& m) {
			this->x = m.x;
			this->y = m.y;
		}
		template<typename U>
		Mat(const Mat<U, 4, 4>& m) {
			this->x = m.x;
			this->y = m.y;
		}

		// Operators

		template<typename U>
		Mat<T, 2, 2>& operator+=(const U& u) {
			this->x += u;
			this->y += u;
			return *this;
		}
		template<typename U>
		Mat<T, 2, 2>& operator+=(const Mat<U, 2, 2>& m) {
			this->x += m.x;
			this->y += m.y;
			return *this;
		}

		template<typename U>
		Mat<T, 2, 2>& operator-=(const U& u) {
			this->x -= u;
			this->y -= u;
			return *this;
		}
		template<typename U>
		Mat<T, 2, 2>& operator-=(const Mat<U, 2, 2>& m) {
			this->x -= m.x;
			this->y -= m.y;
			return *this;
		}

		template<typename U>
		Mat<T, 2, 2>& operator*=(const U& u) {
			this->x *= u;
			this->y *= u;
			return *this;
		}

		template<typename U>
		Mat<T, 2, 2>& operator/=(const U& u) {
			this->x /= u;
			this->y /= u;
			return *this;
		}
		template<typename U>
		Mat<T, 2, 2>& operator/=(const Mat<U, 2, 2>& m) {
			this->x /= m.x;
			this->y /= m.y;
			return *this;
		}

		column_type_ref& operator[](int idx) {
			return columns[idx];
		}
		column_type_cref& operator[](int idx) const {
			return columns[idx];
		}

		component_type_ptr Data() {
			return &_00;
		}
		component_type_cptr Data() const {
			return &_00;
		}

		union {
			struct {
				// 1st column
				component_type _00;
				component_type _10;
				// 2nd column
				component_type _01;
				component_type _11;
			};
			struct {
				column_type right;
				column_type up;
			};
			struct {
				column_type x;
				column_type y;
			};
			struct {
				column_type columns[2];
			};
		};
	};

	// Common Mat2 type declarations

	using Mat2 = Mat<float, 2, 2>;
	using dMat2 = Mat<double, 2, 2>;

	// Mat3 specialization

	template<typename T>
	class Mat<T, 3, 3> {
	public:
		using column_type = Vec<T, 3>;
		using row_type = Vec<T, 3>;

		using column_type_ref = column_type&;
		using column_type_cref = const column_type&;

		using column_type_ptr = column_type*;
		using column_type_cptr = const column_type*;

		using row_type_ref = row_type&;
		using row_type_cref = const row_type&;

		using row_type_ptr = row_type*;
		using row_type_cptr = const row_type*;

		using component_type = typename column_type::component_type;

		using component_type_ref = component_type&;
		using component_type_cref = const component_type&;

		using component_type_ptr = component_type*;
		using component_type_cptr = const component_type*;

		// Constructors

		Mat() : columns() {};
		template<typename U>
		Mat(const U& u) {
			x = column_type{u, 0, 0};
			y = column_type{0, u, 0};
			z = column_type{0, 0, u};
		}

		template<typename X0, typename Y0, typename Z0, // column #0 types
			     typename X1, typename Y1, typename Z1, // column #1 types
			     typename X2, typename Y2, typename Z2> // column #2 types
		Mat(const X0& x0, const Y0& y0, const Z0& z0,   // column #0
			const X1& x1, const Y1& y1, const Z1& z1,   // column #1
			const X2& x2, const Y2& y2, const Z2& z2) { // column #2
			this->x = column_type{x0, y0, z0};
			this->y = column_type{x1, y1, z1};
			this->z = column_type{x2, y2, z2};
		}

		template<typename X, typename Y, typename Z>
		Mat(const Vec<X, 3>& x,   // column #0
			const Vec<Y, 3>& y,   // column #1
			const Vec<Z, 3>& z) { // column #2
			this->x = x;
			this->y = y;
			this->z = z;
		}

		// Converting constructors

		template<typename U>
		Mat(const Mat<U, 2, 2>& m) {
			this->x = m.x;
			this->y = m.y;
			this->z = column_type{m.z, 1};
		}
		template<typename U>
		Mat(const Mat<U, 3, 3>& m) {
			this->x = m.x;
			this->y = m.y;
			this->z = m.z;
		}
		template<typename U>
		Mat(const Mat<U, 4, 4>& m) {
			this->x = m.x;
			this->y = m.y;
			this->z = m.z;
		}

		// Operators

		template<typename U>
		Mat<T, 3, 3>& operator+=(const U& u) {
			this->x += u;
			this->y += u;
			this->z += u;
			return *this;
		}
		template<typename U>
		Mat<T, 3, 3>& operator+=(const Mat<U, 3, 3>& m) {
			this->x += m.x;
			this->y += m.y;
			this->z += m.z;
			return *this;
		}
		
		template<typename U>
		Mat<T, 3, 3>& operator-=(const U& u) {
			this->x -= u;
			this->y -= u;
			this->z -= u;
			return *this;
		}
		template<typename U>
		Mat<T, 3, 3>& operator-=(const Mat<U, 3, 3>& m) {
			this->x -= m.x;
			this->y -= m.y;
			this->z -= m.z;
			return *this;
		}

		template<typename U>
		Mat<T, 3, 3>& operator*=(const U& u) {
			this->x *= u;
			this->y *= u;
			this->z *= u;
			return *this;
		}

		template<typename U>
		Mat<T, 3, 3>& operator/=(const U& u) {
			this->x /= u;
			this->y /= u;
			this->z /= u;
			return *this;
		}
		template<typename U>
		Mat<T, 3, 3>& operator/=(const Mat<U, 3, 3>& m) {
			this->x /= m.x;
			this->y /= m.y;
			this->z /= m.z;
			return *this;
		}

		column_type_ref& operator[](int idx) {
			return columns[idx];
		}
		column_type_cref& operator[](int idx) const {
			return columns[idx];
		}

		component_type_ptr Data() {
			return &_00;
		}
		component_type_cptr Data() const {
			return &_00;
		}

		union {
			struct {
				// 1st column
				component_type _00;
				component_type _10;
				component_type _20;
				// 2nd column
				component_type _01;
				component_type _11;
				component_type _21;
				// 3rd column
				component_type _02;
				component_type _12;
				component_type _22;
			};
			struct {
				column_type right;
				column_type up;
				column_type forward;
			};
			struct {
				column_type x;
				column_type y;
				column_type z;
			};
			struct {
				column_type columns[3];
			};
		};
	};

	// Common Mat3 type declarations

	using Mat3 = Mat<float, 3, 3>;
	using dMat3 = Mat<double, 3, 3>;

	// Mat4 specialization

	template<typename T>
	class Mat<T, 4, 4> {
	public:
		using column_type = Vec<T, 4>;
		using row_type = Vec<T, 4>;

		using column_type_ref = column_type&;
		using column_type_cref = const column_type&;

		using column_type_ptr = column_type*;
		using column_type_cptr = const column_type*;

		using row_type_ref = row_type&;
		using row_type_cref = const row_type&;

		using row_type_ptr = row_type*;
		using row_type_cptr = const row_type*;

		using component_type = typename column_type::component_type;

		using component_type_ref = component_type&;
		using component_type_cref = const component_type&;

		using component_type_ptr = component_type*;
		using component_type_cptr = const component_type*;

		// Constructors

		Mat() : columns() {};
		template<typename U>
		Mat(const U& u) {
			x = column_type{u, 0, 0, 0};
			y = column_type{0, u, 0, 0};
			z = column_type{0, 0, u, 0};
			w = column_type{0, 0, 0, u};
		}

		template<typename X0, typename Y0, typename Z0, typename W0,  // column #0 types
			     typename X1, typename Y1, typename Z1, typename W1,  // column #1 types
			     typename X2, typename Y2, typename Z2, typename W2,  // column #2 types
			     typename X3, typename Y3, typename Z3, typename W3>  // column #3 types
		Mat(const X0& x0, const Y0& y0, const Z0& z0, const W0& w0,   // column #0
			const X1& x1, const Y1& y1, const Z1& z1, const W1& w1,   // column #1
			const X2& x2, const Y2& y2, const Z2& z2, const W2& w2,   // column #2
			const X3& x3, const Y3& y3, const Z3& z3, const W3& w3) { // column #3
			
			this->x = column_type{x0, y0, z0, w0};
			this->y = column_type{x1, y1, z1, w1};
			this->z = column_type{x2, y2, z2, w2};
			this->w = column_type{x3, y3, z3, w3};
		}

		template<typename X, typename Y, typename Z, typename W>
		Mat(const Vec<X, 4>& x,   // column #0
			const Vec<Y, 4>& y,   // column #1
			const Vec<Z, 4>& z,   // column #2
			const Vec<W, 4>& w) { // column #3
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		template<typename U, typename V>
		Mat(const Mat<U, 3, 3>& m, const Vec<V, 3>& v) {
			this->x = column_type{m[0], 0.0f};
			this->y = column_type{m[1], 0.0f};
			this->z = column_type{m[2], 0.0f};
			this->w = column_type{v, 1.0f};
		}

		// Converting constructors

		template<typename U>
		Mat(const Mat<U, 2, 2>& m) {
			this->x = m.x;
			this->y = m.y;
			this->z = column_type{0, 0, 1, 0};
			this->w = column_type{0, 0, 0, 1};
		}
		template<typename U>
		Mat(const Mat<U, 3, 3>& m) {
			this->x = m.x;
			this->y = m.y;
			this->z = m.z;
			this->w = column_type{0, 0, 0, 1};
		}
		template<typename U>
		Mat(const Mat<U, 4, 4>& m) {
			this->x = m.x;
			this->y = m.y;
			this->z = m.z;
			this->w = m.w;
		}

		// Operators

		template<typename U>
		Mat<T, 4, 4>& operator+=(const U& u) {
			this->x += u;
			this->y += u;
			this->z += u;
			this->w += u;
			return *this;
		}
		template<typename U>
		Mat<T, 4, 4>& operator+=(const Mat<U, 4, 4>& m) {
			this->x += m.x;
			this->y += m.y;
			this->z += m.z;
			this->w += m.w;
			return *this;
		}

		template<typename U>
		Mat<T, 4, 4>& operator-=(const U& u) {
			this->x -= u;
			this->y -= u;
			this->z -= u;
			this->w -= u;
			return *this;
		}
		template<typename U>
		Mat<T, 4, 4>& operator-=(const Mat<U, 4, 4>& m) {
			this->x -= m.x;
			this->y -= m.y;
			this->z -= m.z;
			this->w -= m.w;
			return *this;
		}

		template<typename U>
		Mat<T, 4, 4>& operator*=(const U& u) {
			this->x *= u;
			this->y *= u;
			this->z *= u;
			this->w *= u;
			return *this;
		}

		template<typename U>
		Mat<T, 4, 4>& operator/=(const U& u) {
			this->x /= u;
			this->y /= u;
			this->z /= u;
			this->w /= u;
			return *this;
		}
		template<typename U>
		Mat<T, 4, 4>& operator/=(const Mat<U, 4, 4>& m) {
			this->x /= m.x;
			this->y /= m.y;
			this->z /= m.z;
			this->w /= m.w;
			return *this;
		}

		column_type_ref& operator[](int idx) {
			return columns[idx];
		}
		column_type_cref& operator[](int idx) const {
			return columns[idx];
		}

		component_type_ptr Data() {
			return &_00;
		}
		component_type_cptr Data() const {
			return &_00;
		}

		union {
			struct {
				// 1st column
				component_type _00;
				component_type _10;
				component_type _20;
				component_type _30;
				// 2nd column
				component_type _01;
				component_type _11;
				component_type _21;
				component_type _31;
				// 3rd column
				component_type _02;
				component_type _12;
				component_type _22;
				component_type _32;
				// 4rd column
				component_type _03;
				component_type _13;
				component_type _23;
				component_type _33;
			};
			struct {
				column_type right;
				column_type up;
				column_type forward;
				column_type translation;
			};
			struct {
				column_type x;
				column_type y;
				column_type z;
				column_type w;
			};
			struct {
				column_type columns[4];
			};
		};
	};

	// Common Mat4 type declarations

	using Mat4 = Mat<float, 4, 4>;
	using dMat4 = Mat<double, 4, 4>;

	// Operators

	template<typename T, int Rows, int Cols>
	Mat<T, Rows, Cols> operator+(const Mat<T, Rows, Cols>& m1, const Mat<T, Rows, Cols>& m2) {
		Mat<T, Rows, Cols> res{};
		for (int i = 0; i < Cols; i++) {
			res[i] = m1[i] + m2[i];
		}
		return res;
	}

	template<typename T, int Rows, int Cols>
	Mat<T, Rows, Cols> operator-(const Mat<T, Rows, Cols>& m1, const Mat<T, Rows, Cols>& m2) {
		Mat<T, Rows, Cols> res{};
		for (int i = 0; i < Cols; i++) {
			res[i] = m1[i] - m2[i];
		}
		return res;
	}

	template<typename T, int Rows, int Cols>
	Mat<T, Rows, Cols> operator*(const Mat<T, Rows, Cols>& m, const T& t) {
		Mat<T, Rows, Cols> res{};
		for (int i = 0; i < Cols; i++) {
			res[i] = m[i] * t;
		}
		return res;
	}
	template<typename T, int Rows, int Cols>
	Mat<T, Rows, Cols> operator*(const T& t, const Mat<T, Rows, Cols>& m) {
		Mat<T, Rows, Cols> res{};
		for (int i = 0; i < Cols; i++) {
			res[i] = t * m[i];
		}
		return res;
	}
	template<typename T, int Rows, int Cols>
	Vec<T, Rows> operator*(const Mat<T, Rows, Cols>& m, const Vec<T, Cols>& v) {
		Vec<T, Rows> res{};
		for (int i = 0; i < Cols; i++) {
			res += m[i] * v[i];
		}
		return res;
	}
	template<typename T, int Rows, int Cols>
	Vec<T, Cols> operator*(const Vec<T, Rows>& v, const Mat<T, Rows, Cols>& m) {
		Vec<T, Cols> res{};
		for (int i = 0; i < Cols; i++) {
			res[i] =  Dot(v, m[i]);
		}
		return res;
	}
	template<typename T, int Rows, int Cols, int Cols2>
	Mat<T, Rows, Cols2> operator*(const Mat<T, Rows, Cols>& m1, const Mat<T, Cols, Cols2>& m2) {
		Mat<T, Rows, Cols2> res{};
		for (int i = 0; i < Cols2; i++) {
			res[i] = m1 * m2[i];
		}
		return res;
	}

	template<typename T, int Rows, int Cols>
	Mat<T, Rows, Cols> operator/(const Mat<T, Rows, Cols>& m, const T& t) {
		Mat<T, Rows, Cols> res{};
		for (int i = 0; i < Cols; i++) {
			res[i] = m[i] / t;
		}
		return res;
	}
	template<typename T, int Rows, int Cols>
	Mat<T, Rows, Cols> operator/(const T& t, const Mat<T, Rows, Cols>& m) {
		Mat<T, Rows, Cols> res{};
		for (int i = 0; i < Cols; i++) {
			res[i] = t / m[i];
		}
		return res;
	}

	// Functions involving matrices
	// TODO

}