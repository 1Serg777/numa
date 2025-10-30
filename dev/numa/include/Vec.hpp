#pragma once

#include <algorithm>
#include <cmath>

namespace numa {

	template<typename T, int S>
	class Vec {
	public:
		using component_type = T;

		using component_type_ref = component_type&;
		using component_type_cref = const component_type&;

		using component_type_ptr = component_type*;
		using component_type_cptr = const component_type*;

		// Constructors

		Vec() : components() {};
		template<typename U>
		Vec(const U& u) {
			std::fill(components, components + S, static_cast<T>(u));
		}

		// Converting constructors

		template<typename U, int K>
		Vec(const Vec<U, K>& v)
			: Vec() {
			int minDim = std::min(S, K);
			for (int i = 0; i < minDim; i++) {
				components[i] = static_cast<T>(v[i]);
			}
		}

		// Operators

		Vec<T, S> operator-() const {
			Vec<T, S> res{};
			for (int i = 0; i < S; i++) {
				res[i] = -components[i];
			}
			return res;
		}

		template<typename U>
		Vec<T, S>& operator+=(const U& u) {
			for (int i = 0; i < S; i++) {
				components[i] += static_cast<T>(u);
			}
			return *this;
		}
		template<typename U>
		Vec<T, S>& operator+=(const Vec<U, S>& v) {
			for (int i = 0; i < S; i++) {
				components[i] += static_cast<T>(v[i]);
			}
			return *this;
		}
		template<typename U>
		Vec<T, S>& operator-=(const U& u) {
			for (int i = 0; i < S; i++) {
				components[i] -= static_cast<T>(u);
			}
			return *this;
		}
		template<typename U>
		Vec<T, S>& operator-=(const Vec<U, S>& v) {
			for (int i = 0; i < S; i++) {
				components[i] -= static_cast<T>(v[i]);
			}
			return *this;
		}
		template<typename U>
		Vec<T, S>& operator*=(const U& u) {
			for (int i = 0; i < S; i++) {
				components[i] *= static_cast<T>(u);
			}
			return *this;
		}
		template<typename U>
		Vec<T, S>& operator*=(const Vec<U, S>& v) {
			for (int i = 0; i < S; i++) {
				components[i] *= static_cast<T>(v[i]);
			}
			return *this;
		}
		template<typename U>
		Vec<T, S>& operator/=(const U& u) {
			for (int i = 0; i < S; i++) {
				components[i] /= static_cast<T>(u);
			}
			return *this;
		}
		template<typename U>
		Vec<T, S>& operator/=(const Vec<U, S>& v) {
			for (int i = 0; i < S; i++) {
				components[i] /= static_cast<T>(v[i]);
			}
			return *this;
		}

		component_type_ref operator[](int idx) {
			return components[idx];
		}
		component_type_cref operator[](int idx) const {
			return components[idx];
		}

		component_type_ptr Data() {
			return components;
		}
		component_type_cptr Data() const {
			return components;
		}

	private:
		component_type components[S];
	};

	// Vec2 specialization

	template<typename T>
	class Vec<T, 2> {
	public:
		using component_type = T;

		using component_type_ref = component_type&;
		using component_type_cref = const component_type&;

		using component_type_ptr = component_type*;
		using component_type_cptr = const component_type*;

		// Constructors

		Vec() : components() {};
		template<typename U>
		Vec(const U& u) {
			this->x = static_cast<T>(u);
			this->y = static_cast<T>(u);
		}
		template<typename X, typename Y>
		Vec(const X& x, const Y& y) {
			this->x = static_cast<T>(x);
			this->y = static_cast<T>(y);
		}

		// Converting constructors

		template<typename U>
		Vec(const Vec<U, 2>& v) {
			this->x = static_cast<T>(v[0]);
			this->y = static_cast<T>(v[1]);
		}

		// Operators

		Vec<T, 2> operator-() const {
			Vec<T, 2> res{};
			res.x = -this.x;
			res.y = -this.y;
			return res;
		}

		template<typename U>
		Vec<T, 2>& operator+=(const U& u) {
			this->x += static_cast<T>(u);
			this->y += static_cast<T>(u);
			return *this;
		}
		template<typename U>
		Vec<T, 2>& operator+=(const Vec<U, 2>& v) {
			this->x += static_cast<T>(v.x);
			this->y += static_cast<T>(v.y);
			return *this;
		}

		template<typename U>
		Vec<T, 2>& operator-=(const U& u) {
			this->x -= static_cast<T>(u);
			this->y -= static_cast<T>(u);
			return *this;
		}
		template<typename U>
		Vec<T, 2>& operator-=(const Vec<U, 2>& v) {
			this->x -= static_cast<T>(v.x);
			this->y -= static_cast<T>(v.y);
			return *this;
		}

		template<typename U>
		Vec<T, 2>& operator*=(const U& u) {
			this->x *= static_cast<T>(u);
			this->y *= static_cast<T>(u);
			return *this;
		}
		template<typename U>
		Vec<T, 2>& operator*=(const Vec<U, 2>& v) {
			this->x *= static_cast<T>(v.x);
			this->y *= static_cast<T>(v.y);
			return *this;
		}

		template<typename U>
		Vec<T, 2>& operator/=(const U& u) {
			this->x /= static_cast<T>(u);
			this->y /= static_cast<T>(u);
			return *this;
		}
		template<typename U>
		Vec<T, 2>& operator/=(const Vec<U, 2>& v) {
			this->x /= static_cast<T>(v.x);
			this->y /= static_cast<T>(v.y);
			return *this;
		}

		component_type_ref operator[](int idx) {
			return components[idx];
		}
		component_type_cref operator[](int idx) const {
			return components[idx];
		}

		component_type_ptr Data() {
			return components;
		}
		component_type_cptr Data() const {
			return components;
		}

		union {
			struct {component_type x; component_type y;};
			struct {component_type u; component_type v;};
			component_type components[2];
		};
	};

	// Common Vec2 type declarations

	using Vec2 = Vec<float, 2>;
	using dVec2 = Vec<double, 2>;

	using iVec2 = Vec<int, 2>;
	using uVec2 = Vec<unsigned int, 2>;

	using u8Vec2 = Vec<uint8_t, 2>;
	using u16Vec2 = Vec<uint16_t, 2>;
	using u32Vec2 = Vec<uint32_t, 2>;
	using u64Vec2 = Vec<uint64_t, 2>;

	using i8Vec2 = Vec<int8_t, 2>;
	using i16Vec2 = Vec<int16_t, 2>;
	using i32Vec2 = Vec<int32_t, 2>;
	using i64Vec2 = Vec<int64_t, 2>;

	// Vec3 specialization

	template<typename T>
	class Vec<T, 3> {
	public:
		using component_type = T;

		using component_type_ref = component_type&;
		using component_type_cref = const component_type&;

		using component_type_ptr = component_type*;
		using component_type_cptr = const component_type*;

		// Constructors

		Vec() : components() {};
		template<typename U>
		Vec(const U& u) {
			this->x = static_cast<T>(u);
			this->y = static_cast<T>(u);
			this->z = static_cast<T>(u);
		}
		template<typename X, typename Y, typename Z>
		Vec(const X& x, const Y& y, const Z& z) {
			this->x = static_cast<T>(x);
			this->y = static_cast<T>(y);
			this->z = static_cast<T>(z);
		}

		// Converting constructors

		template<typename U, typename Z>
		Vec(const Vec<U, 2>& v, const Z& z) {
			this->x = static_cast<T>(v.x);
			this->y = static_cast<T>(v.y);
			this->z = static_cast<T>(z);
		}
		template<typename U, typename X>
		Vec(const X& x, const Vec<U, 2>& v) {
			this->x = static_cast<T>(x);
			this->y = static_cast<T>(v.x);
			this->z = static_cast<T>(v.y);
		}
		template<typename U>
		Vec(const Vec<U, 3>& v) {
			this->x = static_cast<T>(v.x);
			this->y = static_cast<T>(v.y);
			this->z = static_cast<T>(v.z);
		}

		// Operators

		Vec<T, 3> operator-() const {
			Vec<T, 3> res{};
			res.x = -this.x;
			res.y = -this.y;
			res.z = -this.z;
			return res;
		}

		template<typename U>
		Vec<T, 3>& operator+=(const U& u) {
			this->x += static_cast<T>(u);
			this->y += static_cast<T>(u);
			this->z += static_cast<T>(u);
			return *this;
		}
		template<typename U>
		Vec<T, 3>& operator+=(const Vec<U, 3>& v) {
			this->x += static_cast<T>(v.x);
			this->y += static_cast<T>(v.y);
			this->z += static_cast<T>(v.z);
			return *this;
		}

		template<typename U>
		Vec<T, 3>& operator-=(const U& u) {
			this->x -= static_cast<T>(u);
			this->y -= static_cast<T>(u);
			this->z -= static_cast<T>(u);
			return *this;
		}
		template<typename U>
		Vec<T, 3>& operator-=(const Vec<U, 3>& v) {
			this->x -= static_cast<T>(v.x);
			this->y -= static_cast<T>(v.y);
			this->z -= static_cast<T>(v.z);
			return *this;
		}

		template<typename U>
		Vec<T, 3>& operator*=(const U& u) {
			this->x *= static_cast<T>(u);
			this->y *= static_cast<T>(u);
			this->z *= static_cast<T>(u);
			return *this;
		}
		template<typename U>
		Vec<T, 3>& operator*=(const Vec<U, 3>& v) {
			this->x *= static_cast<T>(v.x);
			this->y *= static_cast<T>(v.y);
			this->z *= static_cast<T>(v.z);
			return *this;
		}

		template<typename U>
		Vec<T, 3>& operator/=(const U& u) {
			this->x /= static_cast<T>(u);
			this->y /= static_cast<T>(u);
			this->z /= static_cast<T>(u);
			return *this;
		}
		template<typename U>
		Vec<T, 3>& operator/=(const Vec<U, 3>& v) {
			this->x /= static_cast<T>(v.x);
			this->y /= static_cast<T>(v.y);
			this->z /= static_cast<T>(v.z);
			return *this;
		}

		component_type_ref operator[](int idx) {
			return components[idx];
		}
		component_type_cref operator[](int idx) const {
			return components[idx];
		}

		component_type_ptr Data() {
			return components;
		}
		component_type_cptr Data() const {
			return components;
		}

		union {
			struct {component_type x; component_type y; component_type z;};
			struct {component_type r; component_type g; component_type b;};
			component_type components[3];
		};
	};

	// Common Vec3 type declarations

	using Vec3 = Vec<float, 3>;
	using dVec3 = Vec<double, 3>;

	using iVec3 = Vec<int, 3>;
	using uVec3 = Vec<unsigned int, 3>;

	using u8Vec3 = Vec<uint8_t, 3>;
	using u16Vec3 = Vec<uint16_t, 3>;
	using u32Vec3 = Vec<uint32_t, 3>;
	using u64Vec3 = Vec<uint64_t, 3>;

	using i8Vec3 = Vec<int8_t, 3>;
	using i16Vec3 = Vec<int16_t, 3>;
	using i32Vec3 = Vec<int32_t, 3>;
	using i64Vec3 = Vec<int64_t, 3>;

	// Vec4 specialization

	template<typename T>
	class Vec<T, 4> {
	public:
		using component_type = T;

		using component_type_ref = component_type&;
		using component_type_cref = const component_type&;

		using component_type_ptr = component_type*;
		using component_type_cptr = const component_type*;

		// Constructors

		Vec() : components() {};
		template<typename U>
		Vec(const U& u) {
			this->x = static_cast<T>(u);
			this->y = static_cast<T>(u);
			this->z = static_cast<T>(u);
			this->w = static_cast<T>(u);
		}
		template<typename X, typename Y, typename Z, typename W>
		Vec(const X& x, const Y& y, const Z& z, const W& w) {
			this->x = static_cast<T>(x);
			this->y = static_cast<T>(y);
			this->z = static_cast<T>(z);
			this->w = static_cast<T>(w);
		}

		// Converting constructors

		template<typename U, typename Z, typename W>
		Vec(const Vec<U, 2>& v, const Z& z, const W& w) {
			this->x = static_cast<T>(v.x);
			this->y = static_cast<T>(v.y);
			this->z = static_cast<T>(z);
			this->w = static_cast<T>(w);
		}
		template<typename U, typename X, typename Y>
		Vec(const X& x, const Y& y, const Vec<U, 2>& v) {
			this->x = static_cast<T>(x);
			this->y = static_cast<T>(y);
			this->z = static_cast<T>(v.x);
			this->w = static_cast<T>(v.y);
		}

		template<typename U, typename V>
		Vec(const Vec<U, 2>& v1, const Vec<V, 2>& v2) {
			this->x = static_cast<T>(v1.x);
			this->y = static_cast<T>(v1.y);
			this->z = static_cast<T>(v2.x);
			this->w = static_cast<T>(v2.y);
		}

		template<typename U, typename W>
		Vec(const Vec<U, 3>& v, const W& w) {
			this->x = static_cast<T>(v.x);
			this->y = static_cast<T>(v.y);
			this->z = static_cast<T>(v.z);
			this->w = static_cast<T>(w);
		}
		template<typename U, typename X>
		Vec(const X& x, const Vec<U, 3>& v) {
			this->x = static_cast<T>(x);
			this->y = static_cast<T>(v.x);
			this->z = static_cast<T>(v.y);
			this->w = static_cast<T>(v.z);
		}

		template<typename U>
		Vec(const Vec<U, 4>& v) {
			this->x = static_cast<T>(v.x);
			this->y = static_cast<T>(v.y);
			this->z = static_cast<T>(v.z);
			this->w = static_cast<T>(v.w);
		}

		// Operators

		Vec<T, 4> operator-() const {
			Vec<T, 4> res{};
			res.x = -this.x;
			res.y = -this.y;
			res.z = -this.z;
			res.w = -this.w;
			return res;
		}

		template<typename U>
		Vec<T, 4>& operator+=(const U& u) {
			this->x += static_cast<T>(u);
			this->y += static_cast<T>(u);
			this->z += static_cast<T>(u);
			this->w += static_cast<T>(u);
			return *this;
		}
		template<typename U>
		Vec<T, 4>& operator+=(const Vec<U, 4>& v) {
			this->x += static_cast<T>(v.x);
			this->y += static_cast<T>(v.y);
			this->z += static_cast<T>(v.z);
			this->w += static_cast<T>(v.w);
			return *this;
		}

		template<typename U>
		Vec<T, 4>& operator-=(const U& u) {
			this->x -= static_cast<T>(u);
			this->y -= static_cast<T>(u);
			this->z -= static_cast<T>(u);
			this->w -= static_cast<T>(u);
			return *this;
		}
		template<typename U>
		Vec<T, 4>& operator-=(const Vec<U, 4>& v) {
			this->x -= static_cast<T>(v.x);
			this->y -= static_cast<T>(v.y);
			this->z -= static_cast<T>(v.z);
			this->w -= static_cast<T>(v.w);
			return *this;
		}

		template<typename U>
		Vec<T, 4>& operator*=(const U& u) {
			this->x *= static_cast<T>(u);
			this->y *= static_cast<T>(u);
			this->z *= static_cast<T>(u);
			this->w *= static_cast<T>(u);
			return *this;
		}
		template<typename U>
		Vec<T, 4>& operator*=(const Vec<U, 4>& v) {
			this->x *= static_cast<T>(v.x);
			this->y *= static_cast<T>(v.y);
			this->z *= static_cast<T>(v.z);
			this->w *= static_cast<T>(v.w);
			return *this;
		}

		template<typename U>
		Vec<T, 4>& operator/=(const U& u) {
			this->x /= static_cast<T>(u);
			this->y /= static_cast<T>(u);
			this->z /= static_cast<T>(u);
			this->w /= static_cast<T>(u);
			return *this;
		}
		template<typename U>
		Vec<T, 4>& operator/=(const Vec<U, 4>& v) {
			this->x /= static_cast<T>(v.x);
			this->y /= static_cast<T>(v.y);
			this->z /= static_cast<T>(v.z);
			this->w /= static_cast<T>(v.w);
			return *this;
		}

		component_type_ref operator[](int idx) {
			return components[idx];
		}
		component_type_cref operator[](int idx) const {
			return components[idx];
		}

		component_type_ptr Data() {
			return components;
		}
		component_type_cptr Data() const {
			return components;
		}

		union {
			struct {component_type x; component_type y; component_type z; component_type w;};
			struct {component_type r; component_type g; component_type b; component_type a;};
			component_type components[4];
		};
	};

	// Common Vec4 type declarations

	using Vec4 = Vec<float, 4>;
	using dVec4 = Vec<double, 4>;

	using iVec4 = Vec<int, 4>;
	using uVec4 = Vec<unsigned int, 4>;

	using u8Vec4 = Vec<uint8_t, 4>;
	using u16Vec4 = Vec<uint16_t, 4>;
	using u32Vec4 = Vec<uint32_t, 4>;
	using u64Vec4 = Vec<uint64_t, 4>;

	using i8Vec4 = Vec<int8_t, 4>;
	using i16Vec4 = Vec<int16_t, 4>;
	using i32Vec4 = Vec<int32_t, 4>;
	using i64Vec4 = Vec<int64_t, 4>;

	// Operators

	template<typename T, int S>
	Vec<T, S> operator+(const Vec<T, S>& v, const T& t) {
		Vec<T, S> res{};
		for (int i = 0; i < S; i++) {
			res[i] = v[i] + t;
		}
		return res;
	}
	template<typename T, int S>
	Vec<T, S> operator+(const T& t, const Vec<T, S>& v) {
		Vec<T, S> res{};
		for (int i = 0; i < S; i++) {
			res[i] = t + v[i];
		}
		return res;
	}
	template<typename T, int S>
	Vec<T, S> operator+(const Vec<T, S>& v1, const Vec<T, S>& v2) {
		Vec<T, S> res{};
		for (int i = 0; i < S; i++) {
			res[i] = v1[i] + v2[i];
		}
		return res;
	}

	template<typename T, int S>
	Vec<T, S> operator-(const Vec<T, S>& v, const T& t) {
		Vec<T, S> res{};
		for (int i = 0; i < S; i++) {
			res[i] = v[i] - t;
		}
		return res;
	}
	template<typename T, int S>
	Vec<T, S> operator-(const T& t, const Vec<T, S>& v) {
		Vec<T, S> res{};
		for (int i = 0; i < S; i++) {
			res[i] = t - v[i];
		}
		return res;
	}
	template<typename T, int S>
	Vec<T, S> operator-(const Vec<T, S>& v1, const Vec<T, S>& v2) {
		Vec<T, S> res{};
		for (int i = 0; i < S; i++) {
			res[i] = v1[i] - v2[i];
		}
		return res;
	}

	template<typename T, int S>
	Vec<T, S> operator*(const Vec<T, S>& v, const T& t) {
		Vec<T, S> res{};
		for (int i = 0; i < S; i++) {
			res[i] = v[i] * t;
		}
		return res;
	}
	template<typename T, int S>
	Vec<T, S> operator*(const T& t, const Vec<T, S>& v) {
		Vec<T, S> res{};
		for (int i = 0; i < S; i++)
		{
			res[i] = t * v[i];
		}
		return res;
	}
	template<typename T, int S>
	Vec<T, S> operator*(const Vec<T, S>& v1, const Vec<T, S>& v2) {
		Vec<T, S> res{};
		for (int i = 0; i < S; i++) {
			res[i] = v1[i] * v2[i];
		}
		return res;
	}

	template<typename T, int S>
	Vec<T, S> operator/(const Vec<T, S>& v, const T& t) {
		Vec<T, S> res{};
		for (int i = 0; i < S; i++) {
			res[i] = v[i] / t;
		}
		return res;
	}
	template<typename T, int S>
	Vec<T, S> operator/(const T& t, const Vec<T, S>& v) {
		Vec<T, S> res{};
		for (int i = 0; i < S; i++) {
			res[i] = t / v[i];
		}
		return res;
	}
	template<typename T, int S>
	Vec<T, S> operator/(const Vec<T, S>& v1, const Vec<T, S>& v2) {
		Vec<T, S> res{};
		for (int i = 0; i < S; i++) {
			res[i] = v1[i] / v2[i];
		}
		return res;
	}

	// Functions involving vectors

	template<typename T, int S>
	Vec<T, S> Min(const Vec<T, S>& v1, const Vec<T, S>& v2) {
		Vec<T, S> res{};
		for (int i = 0; i < S; i++) {
			res[i] = std::min(v1[i], v2[i]);
		}
		return res;
	}
	template<typename T, int S>
	Vec<T, S> Min(const Vec<T, S>& v, const T& t) {
		Vec<T, S> res{};
		for (int i = 0; i < S; i++) {
			res[i] = std::min(v[i], t);
		}
		return res;
	}

	template<typename T, int S>
	Vec<T, S> Max(const Vec<T, S>& v1, const Vec<T, S>& v2) {
		Vec<T, S> res{};
		for (int i = 0; i < S; i++) {
			res[i] = std::max(v1[i], v2[i]);
		}
		return res;
	}
	template<typename T, int S>
	Vec<T, S> Max(const Vec<T, S>& v, const T& t) {
		Vec<T, S> res{};
		for (int i = 0; i < S; i++) {
			res[i] = std::max(v[i], t);
		}
		return res;
	}

	template<typename T, int S>
	Vec<T, S> Clamp(const Vec<T, S>& x, const Vec<T, S>& minVal, const Vec<T, S>& maxVal) {
		// 1. The OpenGL specification uses this method.
		return Min(Max(x, minVal), maxVal);
		// 2. Alternative implementation
		// return Max(Min(x, maxVal), minVal);
	}
	template<typename T, int S>
	Vec<T, S> Clamp(const Vec<T, S>& x, const T& minVal, const T& maxVal) {
		// 1. The OpenGL specification uses this method.
		return Min(Max(x, Vec<T, S>(minVal)), Vec<T, S>(maxVal));
		// 2. Alternative implementation
		// return Max(Min(x, Vec<T, S>(maxVal)), Vec<T, S>(minVal));
	}

	template<typename T, int S>
	T Dot(const Vec<T, S>& v1, const Vec<T, S>& v2) {
		/*
		Vec<T, S> tmp = v1 * v2;
		T res{0};
		for (int i = 0; i < S; i++) {
			res += tmp[i];
		}
		return res;
		*/
		T res{0};
		for (int i = 0; i < S; i++) {
			res += v1[i] * v2[i];
		}
		return res;
	}
	template<typename T, int S>
	Vec<T, S> Cross(const Vec<T, S>& v1, const Vec<T, S>& v2) {
		Vec<T, S> cross;
		// TODO:
		// we should probably limit this operation only to Vec3 (what about Vec4?)
		return cross;
	}

	template<typename T, int S>
	T Length2(const Vec<T, S>& v) {
		return Dot(v, v);
	}
	template<typename T, int S>
	T Length(const Vec<T, S>& v) {
		return static_cast<T>(std::sqrt(Length2(v)));
	}

	template<typename T, int S>
	Vec<T, S> Normalize(const Vec<T, S>& v) {
		return v / Length(v);
	}

}