#include <png++/png.hpp>


constexpr int width = 128;
constexpr int height = 128;

int main() {
	png::image<png::rgb_pixel> image(width, height);
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			image[y][x] = png::rgb_pixel(x, y, x+y);

	image.write("rgb.png");
	
	return 0;
}
