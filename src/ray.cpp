#include "ray.hpp"

// Ray::Ray() : pos(0, 0, 0), _dir(0, 0, -1) { // as good as any direction
// }
Ray::Ray(Point3 pos = Point3(0, 0, 0), Vec3 dir = Vec3(0, 0, -1))
    : _dir(dir.normalized()), pos(pos) {
}

Ray* Ray::advance_by(double t) {
	pos = this->at(t);
	return this;
}
