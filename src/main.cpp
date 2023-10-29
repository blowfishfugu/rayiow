#include <iostream>
#include <numeric>
#include <string>
#include <array>
#include <string_view>

#include "vec3.h" //using point3
#include "color.h" //using color
#include "ppm_ascii.h" //using PixelType

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
			
			auto pixel_color = color{ ratioR,ratioG,b };
			
			write_color(std::cout,pixel_color);
		}
	}
	std::clog << "\rDone                         ";
	return 0;
}