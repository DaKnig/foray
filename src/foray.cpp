#include "canvas.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "scene_object.hpp"
#include "vec3.hpp"

#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

using Color = Vec3;

void draw_demo(Canvas &canvas) {
	Color red = Color(255.999, 0, 0);
	Color green = Color(0, 255.999, 0);

	for (int j = 0; j < canvas.h(); j++) {
		std::clog << "\rLines drawn: " << j << "/" << canvas.h()
		          << std::flush;
		for (int i = 0; i < canvas.w(); i++) {
			Pixel pix = red * (double(i) / (canvas.w() - 1))
			            + green * (double(j) / (canvas.h() - 1));

			canvas.set_pix(i, j, pix);
		}
	}
	std::clog << "\rDone!                                " << std::endl;
}

void draw_sphere(Canvas &canvas) {
	/* scene:       .
            y      /|
	        ^     / |   __
	        |    /  |  /  \
	        |____| ___|  __|__\ -z
	       /     |  | |    |  /
	      /      | /   \__/
	     v       |/
	    x        /
	*/

    // the viewport is represented by that rectangle, camera is at the
	// origin, and a sphere is located on the negative z axis

	// draw the sphere as seen through a view port.



	// the camera is at the origin looking into the negative z direction
	Ray camera(Point3(0, 0, 0), Vec3(0, 0, -1));
	auto focal_length = 1.0;
	auto viewport_height = 1.0;

	Scene scene(camera, focal_length, viewport_height);

	// some object(s) on the scene...
	scene.add_object(std::make_unique<Sphere>(Point3(0, 0, -5), 1.0));
	scene.add_object(std::make_unique<CheckerPlaneXZ>(-100.));
	scene.render(canvas);
}

int main() {
	Canvas canvas(800, 600);
	draw_sphere(canvas);

	std::cout << canvas << std::endl;
	return 0;
}
