#include <iostream>
#include <numeric>
#include <string>
#include <array>
#include <string_view>

#include "vec3.h" //using point3
#include "color.h" //using color
#include "ppm_ascii.h" //using PixelType

#include "ray.h"

//to test if multiplication of vec3 are ok
static void printSampleRay()
{
	ray r{ {0,0,0},{1,1,1} };
	point3 start = r.at(0.0);
	point3 behind = r.at(-1.0);
	point3 end = r.at(1.0);
	point3 beyond = r.at(2.0);
	std::clog << start << '\n';
	std::clog << behind << '\n';
	std::clog << end << '\n';
	std::clog << beyond << '\n';
}

struct canvas {
	using value_type = point3::value_type;
	value_type aspect_ratio{};
	int image_width{};
	int image_height{};
	explicit canvas( value_type wratio, value_type hratio, int width)
		: image_width{ width }, aspect_ratio{ wratio / hratio }
	{
		image_height = static_cast<int>(image_width / aspect_ratio);
		image_height = std::max(image_height, 1);
	}
};

struct viewport {
	using value_type = point3::value_type;
	value_type viewport_height{};
	value_type viewport_width{};
	vec3<value_type> U{};
	vec3<value_type> V{};
	vec3<value_type> pixel_delta_U{};
	vec3<value_type> pixel_delta_V{};
	explicit viewport(value_type height, const canvas& Img)
		:
		viewport_height{height},
		viewport_width{height*(static_cast<value_type>(Img.image_width)/Img.image_height)}
	{
		U = { viewport_width,0,0 };
		V = { 0, -viewport_height,0 };
		pixel_delta_U = U / static_cast<value_type>(Img.image_width);
		pixel_delta_V = V / static_cast<value_type>(Img.image_height);
	}
};

struct camera
{
	using value_type = point3::value_type;
	const canvas& _canvas;
	const viewport& _viewport;
	
	value_type focal_length = 1.0;
	point3 camera_center{}; //0,0,0

	point3 upper_left{};
	point3 pixel00{};
	explicit camera( const canvas& Canvas, const viewport& Viewport)
		: _canvas{ Canvas }, _viewport{ Viewport }
	{
		upper_left=camera_center-point3(0,0,focal_length) - _viewport.U / 2.0 - _viewport.V / 2.0;
		pixel00 = upper_left + 0.5 * (_viewport.pixel_delta_U + _viewport.pixel_delta_V);
	}
};

bool hit_sphere(const point3& center, point3::value_type radius, const ray& r)
{
	vec3 oc = r.origin() - center;
	point3::value_type a = dot(r.direction(), r.direction());
	point3::value_type b = 2.0 * dot(oc, r.direction());
	point3::value_type c = dot(oc, oc) - radius * radius;
	point3::value_type discriminant = b * b - 4 * a * c;
	//(-b +/- sqrt(b+*b-4ac) ) / (2a)
	return discriminant >= 0;
}

color ray_color(const ray& r)
{
	if (hit_sphere(point3{ 0,0,-1 }, 0.5, r)) //sphere on center -1z
	{
		return color{ 1,0,0 };
	}
	vec3<point3::value_type> unit_direction = unit_vector(r.direction());
	point3::value_type y = 0.5 * (unit_direction.y() + 1.0); // -1.0 <= y <= 1.0
	return (1.0 - y) * color { 1.0, 1.0, 1.0 } + y * color{ 0.5,0.7,1.0 }; //lerp color1 to color2
}

int main(int argc, char** argv)
{
	printSampleRay();


	canvas img{ 19.0,6.0,400 };
	viewport view{ 2.0,img };
	camera cam{ img,view };

	ppm_ascii_head head{ img.image_width,img.image_height };
	std::cout << head;
	for (int y = 0; y < img.image_height; ++y)
	{
		std::clog << "\rScanlines remaining: " << (img.image_height - y) << "     " << std::flush;
		for (int x = 0; x < img.image_width; ++x)
		{
			point3 pixel_center{
				cam.pixel00
				+ ((double)x * cam._viewport.pixel_delta_U)
				+ ((double)y * cam._viewport.pixel_delta_V)
			};
			vec3<point3::value_type> ray_direction = pixel_center - cam.camera_center;
			ray r(cam.camera_center, ray_direction);

			auto pixel_color = ray_color(r);
			
			write_color(std::cout,pixel_color);
		}
	}
	std::clog << "\rDone                         ";
	return 0;
}