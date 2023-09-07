#pragma once

#include "ray.hpp"
#include "scene_object.hpp"
#include "canvas.hpp"

#include <memory>
#include <vector>

// class SceneObject;

class Scene {
	Ray camera;
	double focal_length;
	double viewport_height;

	std::vector<std::unique_ptr<SceneObject>> objects;

	Pixel ray_color(Ray&& ray) const;
public:
	Scene(Ray camera = Ray(Point3(0, 0, 0), Vec3(0, 0, -1)),
	      double focal_length = 1, double viewport_height = 1);

	void add_object(std::unique_ptr<SceneObject>new_object);
	void render(Canvas &canvas);
};
