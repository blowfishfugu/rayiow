#include <iostream>
#include <numeric>
#include <string>
#include <array>
#include <string_view>

#include "vec3.h"

struct ppm_ascii_pixel {
	int32_t r{};
	int32_t g{};
	int32_t b{};
};

std::ostream& operator<<(std::ostream& os, ppm_ascii_pixel const& p)
{
	os << p.r << ' ' << p.g << ' ' << p.b << '\n';
	return os;
}

struct ppm_ascii_head {
	const std::string_view magic{ "P3\n" };
	const std::string_view color_max{ "\n255\n"};
	int image_width{};
	int image_height{};
	explicit ppm_ascii_head(int width,int height) 
		: image_width{width},image_height{height}
	{}

};

std::ostream& operator<<(std::ostream& os, ppm_ascii_head const& head)
{
	os	<< head.magic 
		<< head.image_width << ' ' << head.image_height 
		<< head.color_max;
	return os;
}

int main(int argc, char** argv)
{
	ppm_ascii_head head{ 256,256 };
	std::cout << head;
	for (int y = 0; y < head.image_height; ++y)
	{
		std::clog << "\rScanlines remaining: " << (head.image_height - y) << "     " << std::flush;
		for (int x = 0; x < head.image_width; ++x)
		{
			double ratioR = double(x) / (head.image_width - 1);
			double ratioG = double(y) / (head.image_height - 1);
			double b = 0.0;

			ppm_ascii_pixel pxl{
				.r = static_cast<int32_t>(ratioR * 255.999),
				.g = static_cast<int32_t>(ratioG * 255.999),
				.b = static_cast<int32_t>(b * 255.999)
			};
			std::cout << pxl;
		}
	}

	return 0;
}