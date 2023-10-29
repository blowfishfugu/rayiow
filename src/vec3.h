#pragma once
#ifndef VEC3_H
#define VEC3_H
#include <numeric>
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>

#include <type_traits>
#include <concepts>

template<std::floating_point F>
struct vec3
{
	std::array<F,3> e;
	constexpr vec3( F e0, F e1, F e2 ): e{e0,e1,e2}
	{}

	constexpr vec3() :vec3{F{},F{},F{}}
	{}

	constexpr F x() const { return std::get<0>(e); }
	constexpr F& x(){ return std::get<0>(e); }
	constexpr F y() const { return std::get<1>(e); }
	constexpr F& y(){ return std::get<1>(e); }
	constexpr F z() const { return std::get<2>(e); }
	constexpr F& z(){ return std::get<2>(e); }

	constexpr F operator[](int i) const { return e[i]; }
	constexpr F& operator[](int i){ return e[i]; }

	constexpr vec3 operator-() const { return { -x(),-y(),-z() }; }
	constexpr vec3& operator+=(const vec3& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	constexpr vec3& operator*=(const vec3& v)
	{
		e[0] *= v.e[0];
		e[1] *= v.e[1];
		e[2] *= v.e[2];
		return *this;
	}

	constexpr vec3& operator/=(F t)
	{
		return (*this)*=(1 / t);
	}

	constexpr F length_squared() const
	{
		return x() * x() + y() * y() + z() * z();
	}

	constexpr F length() const {
		return std::sqrt(length_squared());
	}
};

using point3 = vec3<double>;

template<std::floating_point T>
inline std::ostream& operator<<(std::ostream& os, const vec3<T>& v)
{
	return os << v[0] << ' ' << v[1] << ' ' << v[2];
}

template<std::floating_point T>
inline vec3<T> operator+(const vec3<T>& l, const vec3<T>& r)
{
	return {
		l[0]+r[0],
		l[1]+r[1],
		l[2]+r[2]
	};
}

template<std::floating_point T>
inline vec3<T> operator-(const vec3<T>& l, const vec3<T>& r)
{
	return {
		l[0] - r[0],
		l[1] - r[1],
		l[2] - r[2]
	};
}

template<std::floating_point T>
inline vec3<T> operator*(const vec3<T>& l, const vec3<T>& r)
{
	return {
		l[0] * r[0],
		l[1] * r[1],
		l[2] * r[2]
	};
}

template<std::floating_point T>
inline vec3<T> operator*(const vec3<T>& v, T t)
{
	return t * v;
}

template<std::floating_point T>
inline vec3<T> operator/(const vec3<T>& v, T t)
{
	return (1/t) * v;
}

template<std::floating_point T>
inline T dot(const vec3<T>& l, const vec3<T>& r)
{
	return
		l[0] * r[0] +
		l[1] * r[1] +
		l[2] * r[2];
}

template<std::floating_point T>
inline vec3<T> cross(const vec3<T>& l, const vec3<T>& r)
{
	return{
		l[1]*r[2]- l[2]*r[1], //yz-zy
		l[2]*r[0]- l[0]*r[2], //zx-xz
		l[0]*r[1]- l[1]*r[0], //xy-yx
	};

}

template<std::floating_point T>
inline vec3<T> unit_vector(const vec3<T>& v) {
	return v / v.length();
}

#endif