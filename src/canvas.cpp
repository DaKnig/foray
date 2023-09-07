#include "canvas.hpp"

Pixel::Pixel(Vec3 vec) : r(vec.x), g(vec.y), b(vec.z) {
}

using std::ostream;

ostream& operator<<(ostream& os, Pixel const& pixel) {
	return os << (int)pixel.r << " " << (int)pixel.g << " " << (int)pixel.b
	          << " ";
}

Canvas::Canvas(int widht, int height)
    : width(widht), height(height), canvas(width * height) {
}

void Canvas::set_pix(int x, int y, Pixel pix) {
	this->canvas[y * width + x] = pix;
}

Pixel Canvas::get_pix(int x, int y) const {
	return this->canvas[y * width + x];
}

ostream& operator<<(ostream& os, Canvas const& canvas) {
	os << "P3\n" << canvas.width << " " << canvas.height << "\n";
	os << "256\n"; // depth
	for (int y = 0; y < canvas.height; y++) {
		for (int x = 0; x < canvas.width; x++) {
			os << canvas.get_pix(x, y) << "\n";
		}
	}
	return os;
}
