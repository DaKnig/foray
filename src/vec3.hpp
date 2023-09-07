#pragma once
#include <ostream>

struct Vec3 {
	double x, y, z;

	Vec3();
	Vec3(double x, double y, double z);

	double length() const;
	double length_squared() const;
	Vec3 normalized() const;
	double dot(Vec3 other) const;

	Vec3 operator+=(Vec3 other);
	Vec3 operator-=(Vec3 other);
	Vec3 operator+(Vec3 other) const;
	Vec3 operator-(Vec3 other) const;

	Vec3 operator*=(double t);
	Vec3 operator*(double t) const;
	friend Vec3 operator*(double t, Vec3 vec);
	Vec3 operator/(double t) const;

	Vec3 operator-() const;

	friend std::ostream &operator<<(std::ostream &out, const Vec3 &v);
};

using Point3 = Vec3; // for clarity, position vs vector
using Color = Vec3; // idealistic color, rgb, 24bit
