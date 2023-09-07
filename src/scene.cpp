#include "scene.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <cmath>
#include <chrono>

using Color = Vec3;

Scene::Scene(Ray camera, double focal_length, double viewport_height)
    : camera(camera), focal_length(focal_length),
      viewport_height(viewport_height), objects() {
}

void Scene::add_object(std::unique_ptr<SceneObject> new_object) {
	this->objects.emplace_back(std::move(new_object));
}

inline Color skybox(Vec3 dir) {
	auto a = 0.5 * (dir.y + 1.0);
	return (1.0 - a) * Color(255, 255, 255) + a * Color(128, 192, 255);	
}

Pixel Scene::ray_color(Ray&& ray) const {
	if (ray.pos.length_squared() > 1000'000. * 1000'000.) {
		// we are at the skybox. return a sky.
		return skybox(ray.dir());
	}
	// try to march the ray!
	auto min_distance = std::numeric_limits<double>::max();
	auto Epsilon = 0.0001;
	for (auto& object : objects) {
		auto distance = object->distance(ray.pos);
		min_distance = std::min(distance, min_distance);

		// have we hit an object?
		if(distance < Epsilon) {
			// if so, let the object color itself
			auto obj_color = object->pixel_color(ray.pos);
			auto skybox_color = skybox(ray.dir());

			auto distance = (ray.pos - camera.pos).length();
			auto a = exp2(-distance/300);

			auto result = a * obj_color + (1 - a) * skybox_color;

			return result;
		}
	}

	// now we know we can advance `min_distance` units forwards
	ray.pos = ray.at(min_distance);
	
	return ray_color(std::move(ray));
}

void Scene::render(Canvas &canvas) {

	auto aspect_ratio = double(canvas.w()) / canvas.h();
	auto viewport_width = viewport_height * aspect_ratio;

	// vector "to the right" across the whole viewport
	Vec3 viewport_u(viewport_width, 0, 0);
	// vector "down" across the whole viewport
	Vec3 viewport_v(0, -viewport_height, 0);

	// now the same vectors, across one pixel
	Vec3 pixel_u = viewport_u / canvas.w();
	Vec3 pixel_v = viewport_v / canvas.h();

	// center of the viewport
	Vec3 viewport_center = camera.at(focal_length);
	Vec3 top_left = viewport_center - viewport_u / 2 - viewport_v / 2;

	// let's start sending some rays!
	// static_assert(top_left + canvas.w() * pixel_u + canvas.h() * pixel_v
	//               == viewport_center + viewport_u / 2 + viewport_v / 2);
	auto worst_pixel_i = 0, worst_pixel_j = 0;
	auto worst_duration = std::chrono::system_clock::duration::zero();
	for (int j = 0; j < canvas.h(); j++) {
		std::clog << "\rLines drawn: " << j << "/" << canvas.h()
		          << std::flush;
		for (int i = 0; i < canvas.w(); i++) {
			Ray ray(camera.pos, top_left + (i + 0.5) * pixel_u
			                        + (j + 0.5) * pixel_v - camera.pos);

			// measure time
			auto before = std::chrono::system_clock::now();
			Pixel pix = this->ray_color(std::move(ray));
			auto after = std::chrono::system_clock::now();
			auto duration = after - before;
			if (worst_duration < duration) {
				worst_pixel_i = i;
				worst_pixel_j = j;
				worst_duration = duration;
			}

			canvas.set_pix(i, j, pix);
		}
	}
	std::clog << "\rDone!                                " << std::endl;

	std::clog << "worst performer: (" << worst_pixel_i << ", "
	          << worst_pixel_j << ") = " << worst_duration << std::endl;
}
