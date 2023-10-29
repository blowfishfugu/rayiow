#pragma once
#ifndef RAY_H
#define RAY_H
#include <type_traits>
#include <concepts>

#include "vec3.h"

struct ray
{
	using value_type = point3::value_type;
	ray() = default;
	
	ray(const point3& origin, const vec3<value_type>& direction)
		: orig{origin},dir{direction}
	{}

	const point3& origin() const { return orig; }
	const vec3<value_type>& direction() const { return dir; }

	point3 at(value_type t) const
	{
		return orig + t*dir;
	}

	point3 orig;
	vec3<value_type> dir;
};

#endif