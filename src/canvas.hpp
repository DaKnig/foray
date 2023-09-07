#pragma once

#include "vec3.hpp"

#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

// using std::vector;

struct Pixel {
	uint8_t r, g, b;
	friend std::ostream& operator<<(std::ostream& os, Pixel const& pixel);
	Pixel(Vec3 vec);
	Pixel() : r(0), g(0), b(0) {
	}
};

class Canvas {
	int width, height;
	std::vector<Pixel> canvas;

public:
	Canvas(int widht, int height);
	void set_pix(int x, int y, Pixel pix);
	Pixel get_pix(int x, int y) const;
	friend std::ostream& operator<<(std::ostream& os, Canvas const& canvas);
	inline int w() const {
		return this->width;
	}
	inline int h() const {
		return this->height;
	}
};
