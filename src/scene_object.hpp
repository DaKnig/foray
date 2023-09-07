#pragma once
#include "ray.hpp"
#include "vec3.hpp"
#include "canvas.hpp"

#include <ranges>

class SceneObject {
public:
	virtual double distance(Point3 point) const = 0;
	virtual Color pixel_color(Point3 point) const = 0;
	virtual ~SceneObject() {};
};

class Sphere : public SceneObject {
public:
	Point3 center;
	double r;
	double r2; // r squared

	Sphere(Point3 center, double r);

	double distance(Point3 point) const override;
	Color pixel_color(Point3 point) const override;
};

class CheckerPlaneXZ: public SceneObject {
	// y = d plane.
	// checkerboard pattern.
	double d;
public:
	CheckerPlaneXZ(double d = -100);

	double distance(Point3 point) const override;
	Color pixel_color(Point3 point) const override;
};
