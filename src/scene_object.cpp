#include "scene_object.hpp"

#include <cassert>
#include <cmath>

double Sphere::distance(Point3 point) const {
	return (center - point).length() - r;
}

Sphere::Sphere(Point3 center, double r) {
	this->center = center;
	this->r = r;
	this->r2 = r*r;
}

Color Sphere::pixel_color(Point3 point) const {
	// assert((point - center).length_squared() - r2 < 0.0021);
	auto dir = (point - center).normalized() / 2 + Vec3(0.5, 0.5, 0.5);
	// auto moved_dir =
	return 255.999 * Vec3(dir.x, dir.y, dir.z);
}

CheckerPlaneXZ::CheckerPlaneXZ(double d) : d(d) {
}

double CheckerPlaneXZ::distance(Point3 point) const {
	return point.y - d;
}

Vec3 CheckerPlaneXZ::pixel_color(Point3 point) const {
	if (std::signbit(point.x)) { point.x = 64 - point.x; }
	if (std::signbit(point.z)) { point.z = 64 - point.z; }
	int x_checkerboard = point.x/64;
	int z_checkerboard = point.z/64;

	auto checkerboard = (x_checkerboard ^ z_checkerboard) & 1;

	return checkerboard ? Vec3(51, 255, 255) : Vec3(0, 102, 102);
}
