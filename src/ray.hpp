#pragma once
#include "vec3.hpp"

class Ray {
	Vec3 _dir; // normalized
public:
	Point3 pos;

	Ray();
	Ray(Point3 pos, Vec3 dir);

	inline Point3 at(double t) const {
		return pos + _dir * t;
	}
	inline Vec3 dir() const {
		return _dir;
	}

	Ray* advance_by(double t);
};
