#pragma once
#ifndef PPM_ASCII_H
#define PPM_ASCII_H
#include "color.h"

struct ppm_ascii_pixel {
	int32_t r{};
	int32_t g{};
	int32_t b{};
	constexpr explicit ppm_ascii_pixel(double _r, double _g, double _b) :
		r{ static_cast<int32_t>(_r * 255.999) },
		g{ static_cast<int32_t>(_g * 255.999) },
		b{ static_cast<int32_t>(_b * 255.999) }
	{}
	constexpr explicit ppm_ascii_pixel(const color& c) :
		ppm_ascii_pixel{ c[0],c[1],c[2] }
	{}
};

inline std::ostream& operator<<(std::ostream& os, ppm_ascii_pixel const& p)
{
	os << p.r << ' ' << p.g << ' ' << p.b;
	return os;
}

struct ppm_ascii_head {
	const std::string_view magic{ "P3\n" };
	const std::string_view color_max{ "\n255\n" };
	int image_width{};
	int image_height{};
	explicit ppm_ascii_head(int width, int height)
		: image_width{ width }, image_height{ height }
	{}

};

inline std::ostream& operator<<(std::ostream& os, ppm_ascii_head const& head)
{
	os << head.magic
		<< head.image_width << ' ' << head.image_height
		<< head.color_max;
	return os;
}

template<typename PixelType = ppm_ascii_pixel>
inline void write_color(std::ostream& os, const color& c)
{
	os << PixelType{ c } << '\n';
}

#endif