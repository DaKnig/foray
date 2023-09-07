#include "vec3.hpp"

#include <cmath>

Vec3::Vec3() : x(0), y(0), z(0) {
}
Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {
}

double Vec3::length_squared() const {
	return x * x + y * y + z * z;
}

double Vec3::length() const {
	return sqrt(x * x + y * y + z * z);
}
Vec3 Vec3::normalized() const {
	return *this / this->length();
}
double Vec3::dot(Vec3 other) const {
	return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::operator+=(Vec3 other) {
	*this = *this + other;
	return *this;
}
Vec3 Vec3::operator+(Vec3 other) const {
	return Vec3(x + other.x, y + other.y, z + other.z);
}
Vec3 Vec3::operator-=(Vec3 other) {
	return *this += -other;
}
Vec3 Vec3::operator-(Vec3 other) const {
	return *this + -other;
}

Vec3 Vec3::operator*=(double t) {
	*this = *this * t;
	return *this;
}
Vec3 Vec3::operator*(double t) const {
	return Vec3(t * x, t * y, t * z);
}
Vec3 Vec3::operator/(double t) const {
	return *this * (1 / t);
}
Vec3 operator*(double t, Vec3 vec) {
	return vec * t;
}

Vec3 Vec3::operator-() const {
	return Vec3(-x, -y, -z);
}

std::ostream &operator<<(std::ostream &out, const Vec3 &v) {
	return out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}
